export default class TableDivItem extends React.Component{
    constructor(props){
        super(props);
    }

    render(){
        const id = this.props.id;
        const value = this.props.value;
        var className = "";
        const selected = this.props.selected;
        for (let sel in selected){
            if (selected[sel].bh == id){
                className += "table_selected";
                break;
            }
        }

        return (
            <tr className={className}>
                <th>{id}</th>
                <th>{value}</th>
            </tr>
        );
    }
}