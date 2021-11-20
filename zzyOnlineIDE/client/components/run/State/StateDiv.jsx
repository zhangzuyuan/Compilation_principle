export default class StateDiv extends React.Component{
    constructor(props) {
        super(props);

        this.state = {
            buffer:[],
            input: ""
        }

        this.nextCode = this.nextCode.bind(this);
        this.inputChange = this.inputChange.bind(this);
        this.submit = this.submit.bind(this);
        this.keyPress = this.keyPress.bind(this);
    }

    nextCode(){
        this.props.nextCode();
    }

    keyPress(e){
        if(e.which == 13)
            this.submit();
    }

    submit() {
        let arr = [];
        let flag = false;
        if(this.state.input == "")
            return;
        arr = this.state.input.split(" ").filter((num)=> num != "" ).map(function(num){
            num = parseInt(num);
            flag = flag || isNaN(num);
            return num;
        });
        this.setState({
            input: ""
        });
        if (flag){
            alert("不合法的输入,请重新输入");
            return;
        }
        let buf = this.state.buffer + arr.join(" ") + "\n";
        this.setState({
            buffer: buf
        });
        this.props.input(arr);
    }

    inputChange(e) {
        this.setState({input:e.target.value});
    }

    render() {
        let s = this.props.stateT;
        let stack = s.stack.map((st,i)=> <th key={i}>{st.toString()}</th>);
        let write_buf = s.write_buf;
        let buffer = this.state.buffer;
        let input = this.state.input;

        return (
            <div>
                <table border="1" className="code_table">
                    <tbody>
                        <tr>
                            <th>I</th>
                            <th>T</th>
                            <th>P</th>
                            <th>B</th>
                        </tr>
                        <tr>
                            <th>{s.I}</th>
                            <th>{s.T}</th>
                            <th>{s.P}</th>
                            <th>{s.B}</th>
                        </tr>
                    </tbody>
                </table>

                <table border="1" className="stack">
                    <tbody>
                        <tr>
                            {stack}
                        </tr>
                    </tbody>
                </table>

                <div>
                    输入字符: <textarea value={buffer} readOnly="readonly"></textarea>
                </div>

                <div>
                    输出字符: <textarea value={write_buf} readOnly="readonly"></textarea>
                </div>

                <div>
                    输入框: <input value={input} onChange={this.inputChange} onKeyPress={this.keyPress}></input>
                </div>
                
                <button onClick={this.submit}>提交</button>
                <button onClick={this.nextCode}>下一条语句</button>
            </div>
        )
    }
}