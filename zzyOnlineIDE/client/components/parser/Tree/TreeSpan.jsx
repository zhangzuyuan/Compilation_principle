export default class TreeSpan extends React.Component{
    constructor(props){
        super(props);

        this.spanMouseEnter = this.spanMouseEnter.bind(this);
        this.spanMouseLeave = this.spanMouseLeave.bind(this);
    }

    spanMouseEnter() {
        let obj = this.props.obj;
        this.props.spanMouseEnter(obj.l, obj.r);
    }

    spanMouseLeave() {
        this.props.spanMouseEnter(0, 0);
    }

    render(){
        let obj = this.props.obj;
        let children = obj.children;
        let unflod = "";
        let value = obj.value || obj.lx;
        if ( children && children.length){
            if(obj.unflod)
                unflod = <i id={obj.id} onClick={this.props.iClick} className="fa fa-minus-circle"></i>
            else
                unflod = <i id={obj.id} onClick={this.props.iClick} className="fa fa-plus-circle"></i>
        }

        return (
            <span onMouseEnter = {this.spanMouseEnter} onMouseLeave = {this.spanMouseLeave}>{unflod}{value}</span>
        );
    }
}