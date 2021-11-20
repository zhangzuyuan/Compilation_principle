export default class ParserCodeDivItem extends React.Component{
    constructor(props) {
        super(props)

        this.itemClicked = this.itemClicked.bind(this);
    }

    itemClicked() {
        this.props.itemClicked([this.props.eys]);
    }

    render() {
        const tolx = ["blz", "fh", "bsf", "cl"];
        let lx = tolx[this.props.eys.lx];
        let name = this.props.eys.value;
        const id = this.props.eys.id;
        var isSelected = "";
        var selected = this.props.selected;
        for (let sel in selected) {
            if (selected[sel].id == id){
                isSelected = "yffx_code_selected";
                break;
            }
        }
        var className = `${lx} ${isSelected} ${name}`;
        return(
            <span onClick={this.itemClicked} className={className}>{this.props.eys.value}</span>
        );
    }
}