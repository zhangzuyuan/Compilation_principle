import Tree from "../../components/parser/Tree/Tree.jsx";
import CodeDiv from "../../components/public/Code/CodeDiv.jsx";

import './ParserView.css'

class ViewTable extends React.Component{
    constructor(props){
        super(props);

        this.state = {
            selected:[]
        };

        this.select = this.select.bind(this);
    }

    itemClicked() {
        return;
    }

    select(l, r) {
        this.setState({
            selected: (Array.from(new Array(r).keys()).slice(l)).map(i=>{return {id:i}})
        });
    }

    render() {
        console.log(this.state);
        return (
            <div>
                <h1>语法分析</h1>
                <div className="view_table">
                    <div className="code_div"><CodeDiv itemClicked={this.itemClicked} selected={this.state.selected} /></div>
                    <Tree select={this.select}/>
                </div>
            </div>
        );
    }
}

ReactDOM.render(
    <ViewTable/>,
    document.getElementById("root")
);
