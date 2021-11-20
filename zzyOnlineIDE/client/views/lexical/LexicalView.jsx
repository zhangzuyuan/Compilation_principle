import CodeDiv from "../../components/public/Code/CodeDiv.jsx";
import EysDiv from "../../components/lexical/Eys/EysDiv.jsx";
import TableDiv from "../../components/lexical/Table/TableDiv.jsx";

import './lexicalView.css'

class ViewTable extends React.Component {
    constructor (props) {
        super(props);

        this.state = {
            selected:[{
                id: 0,
                lx: 0
            }]
        };

        this.itemClicked = this.itemClicked.bind(this);
    }

    itemClicked(selectedItems) {
        this.setState({
            selected: selectedItems
        });
    }

    render() {
        return (
            <div>
                <h1>词法分析</h1>‘
                <div className = "view_table">
                    <CodeDiv itemClicked={this.itemClicked} selected={this.state.selected} />
                    <EysDiv itemClicked={this.itemClicked} selected={this.state.selected}/>
                    <TableDiv itemClicked={this.itemClicked} selected={this.state.selected}/>
                </div>
            </div>
        );
    }
}

ReactDOM.render(
    <ViewTable/>,
    document.getElementById("root")
);
