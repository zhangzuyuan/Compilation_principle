export default class CodeDivItem extends React.Component {
    constructor(props) {
        super(props);

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
        console.log('inCodeDivItem');
        console.log(this.props.selected);
        let howSelected = selected.length == 1 ? "code_selected" : "code_muti_selected";
        for (let sel in selected) {
            if (selected[sel].id == id) {
                isSelected = howSelected;
                break;
            }
        }
        var className = `${lx} ${isSelected} ${name}`;
        return(
            <span onClick={this.itemClicked} className={className}>{this.props.eys.value}</span>
        );
    }
}