export default class EysDivItem extends React.Component{
    constructor(props){
        super(props);

        this.itemClicked = this.itemClicked.bind(this);
    }

    itemClicked(){
        this.props.itemClicked([this.props.eys]);
    }

    render(){
        const lx = this.props.eys.lx;
        const bh = this.props.eys.bh;
        const id = this.props.eys.id;
        const value = this.props.eys.value;
        var className = "";
        var selected = this.props.selected;
        for(let sel in selected){
            if(selected[sel].id == id){
                className += " eys_selected";
                break;
            }
        }
        return(
            <tr className={className} onClick={this.itemClicked}>
                <th>{id}</th>
                <th>{value}</th>
                <th>{lx}</th>
                <th>{bh}</th>
            </tr>
        );
    }
}