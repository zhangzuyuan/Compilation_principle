import ajax from '../../../lib/superagent';

import TableDivItem from './TableDivItem.jsx';

import './TableDiv.css';

export default class TableDiv extends React.Component{
    constructor(props){
        super(props);

        this.state = {
            table: [],
            tableName:""
        }

        this.getTable = this.getTable.bind(this);
    }

    getTable(){
        const toTableFileName = ["blz", "fh", "bsf", "cl"];
        const toTableName = ["保留字", "符号", "标识符", "常量"];
        const lx = this.props.selected[0].lx;
        const tableFileName = toTableFileName[lx];
        const tableName = toTableName[lx];

        var table = [];
        ajax.get(`/compiler/tableFiles/${tableFileName}.table.json`)
            .end((err,res)=>{
                this.setState({
                    table: JSON.parse(res.text),
                    tableName: tableName
                });
            });
    }

    render() {
        const selected = this.props.selected;
        const tableName = this.state.tableName;
        const tableDivItems = this.state.table.map(
            function(tr) {
                return <TableDivItem key={tr.id} id={tr.id} value={tr.value} selected={selected}/>
            }
        );
        if (tableName === "")
            return (
                <div id="table_div" className="view_item"></div>
            );
        return (
            <div id="table_div" className="view_item">
                <center><h2 id="table_name">{tableName}表</h2></center>
                <table border="1" className="table_table">
                    <tbody>
                        <tr>
                            <th>编号</th>
                            <th>值</th>
                        </tr>
                        {tableDivItems}
                    </tbody>
                </table>
            </div>
        );
    }
}