import ajax from '../../lib/superagent';

import RunCodeDiv from '../../components/run/Code/RunCodeDiv.jsx';
import StateDiv from '../../components/run/State/StateDiv.jsx';

import './RunView.css'

class ViewTable extends React.Component {
    constructor(props) {
        super(props)

        this.state = {
            I: {},
            P: 0,
            T: 3,
            B: 0,
            stack: [-1, -1, -1],
            codes: [],
            opr_table: [],
            buffer: [],
            write_buf: [],
            buf_ptr: 0,
            shut_down: false
        };

        this.nextCode = this.nextCode.bind(this);
        this.input = this.input.bind(this);
    }

    componentDidMount() {
        ajax.get('/compiler/jsonFiles/semanticAns.json')
            .end((err, res) => {
                this.setState({
                    codes: JSON.parse(res.text)
                });
            });
        ajax.get('/compiler/inFiles/opr.json')
            .end((err, res) => {
                this.setState({
                    opr_table: JSON.parse(res.text)
                });
            });
    }

    newBuffer(buffer) {
        this.setState({buffer});
    }

    nextCode(){
        let {I, P, T, B, stack, codes, opr_table, buffer, write_buf, buf_ptr, shut_down} = this.state;
        if(shut_down) {
            alert("程序已经结束了");
            return;
        }
        I = codes[P++];
        let l,b,t,a;
        switch (I.f){
            case "LIT":
                stack[T++] = I.a;
                break;
            case "LOD":
                l = I.l;
                b = B;
                for (let i = 0; i < l; i++)
                    b = stack[b];
                stack[T++] = stack[b + I.a];
                break;
            case "STO":
                l = I.l;
                b = B;
                for (let i = 0; i < l; i++)
                    b = stack[b];
                stack[b + I.a] = stack[--T];
                break;
            case "CAL":
                t = T;
                //静态链
                stack[T++] = I.l == 0 ? B : stack[B];
                //动态链
                stack[T++] = B;
                //返回地址
                stack[T++] = P;

                P = I.a;
                B = t;
                break;
            case "INT":
                for (let i = 3; i < I.a; i ++) {
                    stack[T++] = 0;
                }
                break;
            case "JMP":
                P = I.a;
                break;
            case "JPC":
                if (!stack[--T])
                    P = I.a;
                break;
            case "OPR":
                switch (I.a) {
                    case opr_table["return"]:
                        if (stack[B] == -1) {
                            shut_down = true;
                            break;
                        }
                        T = B;
                        P = stack[B + 2];
                        B = stack[B + 1];
                        break;
                    case opr_table["read"]:
                        if (buf_ptr >= buffer.length) {
                            alert("等待输入字符");
                            P--;
                        } else
                            stack[T++] = buffer[buf_ptr++];
                        break;
                    case opr_table["write"]:
                        write_buf += stack[--T].toString() + '\n';
                        break;
                    case opr_table["+"]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a + b;
                        break;
                    case opr_table["-"]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a - b;
                        break;
                    case opr_table["*"]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a * b;
                        break;
                    case opr_table["/"]:
                        b = stack[--T];
                        a = stack[--T];
                        if (b == 0) {
                            alert("整数被0除");
                            shut_down = true;
                            break;
                        }
                        stack[T++] = a / b;
                        break;
                    case opr_table["="]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a === b;
                        break;
                    case opr_table["#"]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a != b;
                        break;
                    case opr_table["<"]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a < b;
                        break;
                    case opr_table["<="]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a <= b;
                        break;
                    case opr_table[">"]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a > b;
                        break;
                    case opr_table[">="]:
                        b = stack[--T];
                        a = stack[--T];
                        stack[T++] = a >= b;
                        break;
                }
                break;
        }
        if(T > 100){
            alert("爆栈,请检查程序是否存在无限递归");
            shut_down = true;
        }
        this.setState({I, P, T, B, stack, codes, opr_table, buffer, write_buf, buf_ptr, shut_down});
    }

    input(arrays) {
        let newBuffer = this.state.buffer;
        newBuffer = newBuffer.concat(arrays);
        this.setState({
            buffer:newBuffer
        });
    }

    render() {
        let code = this.state.codes[this.state.P];
        let stateT = {
            I: code && `${code.f} ${code.l} ${code.a}`,
            P: this.state.P,
            T: this.state.T,
            B: this.state.B,
            stack: this.state.stack,
            codes: this.state.codes,
            buffer: this.state.buffer,
            write_buf: this.state.write_buf
        }
        stateT.stack = stateT.stack.slice(0, stateT.T);

        return (
            <div>
                <h1>run</h1>
                <div className="view_table">
                    <RunCodeDiv nextCode={this.nextCode} state={{codes: this.state.codes, P:this.state.P}} />
                    <StateDiv nextCode={this.nextCode} input={this.input} stateT={stateT}/>
                </div>
            </div>
        );
    }
}


ReactDOM.render(
    <ViewTable/>,
    document.getElementById("root")
);
