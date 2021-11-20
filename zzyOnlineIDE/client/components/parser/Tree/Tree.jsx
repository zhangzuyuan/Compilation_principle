import ajax from '../../../lib/superagent';

import TreeSpan from './TreeSpan.jsx';

import './Tree.css';

export default class Tree extends React.Component{
    constructor(props){
        super(props);

        this.state = {
            data: []
        };
        
        this.toObj = this.toObj.bind(this);
        this.toTree = this.toTree.bind(this);
        this.iClick = this.iClick.bind(this);
        this.spanMouseEnter = this.spanMouseEnter.bind(this);
    }

    toObj(data, id){
        let root = {
            id: id,
            codel: data[id]["codel"],
            coder: data[id]["coder"],
            l: data[id]["l"],
            r: data[id]["r"],
            lx: data[id]["lx"],
            value: data[id]["value"],
            unflod: true,
            children:[]
        };
        data.forEach(obj => {
            if(obj["pid"] == id){
                root.children.push(this.toObj(data, obj["id"]));
            }
        });
        return root;
    }

    toTree(data) {
        let roots = [];
        data.forEach(obj => {
            if(obj["pid"] == -1){
                roots.push(this.toObj(data, obj["id"]));
            }
        });

        this.setState({
            data: roots
        });
    }

    componentDidMount() {
        ajax.get('/compiler/jsonFiles/parseAns.json')
            .end((err, res) => {
                this.toTree(JSON.parse(res.text));
            });
    }

    findUnflod(data, id) {
        return data.map(obj => {
            if(id == obj.id){
                obj.unflod = !obj.unflod;
            }
            obj.children = this.findUnflod(obj.children, id);
            return obj;
        });
    }

    iClick(e) {
        //console.log(e.target.id);
        let id = e.target.id;
        let data = this.state.data;
        this.setState({
            data: this.findUnflod(data, id)
        });
    }

    spanMouseEnter(l, r){
        this.props.select(l, r);
    }

    getTreeList(data, show) {
        let ulDisplay = show ? '' : 'none';

        let lis = data.map(single => {
            let children = single.children;
            let sons = "";
            if(children && children.length) {
                sons = this.getTreeList(children, single.unflod);
            }

            return (
                <li key = {single.id}>
                    <TreeSpan obj ={single} spanMouseEnter={this.spanMouseEnter} iClick ={this.iClick} />
                    {sons}
                </li>
            )
        });

        return (
            <ul style ={{display:ulDisplay}}>
                {lis}
            </ul>
        );
    }

    render() {
        if (!this.state.data.length)
            return <div></div>
        else {
            return (
                <div className = "tree">
                    {this.getTreeList(this.state.data, true)}
                </div>
            );
        }
    }
}