import ajax from '../../../lib/superagent'

import ParserCodeDivItem  from './ParserCodeDivItem.jsx';

import './ParserCodeDiv.css';

export default class ParserCodeDiv extends React.Component{
    constructor(props) {
        super(props);

        this.state = {
            code: "",
            eyss: []
        }

        this.componentDidMount = this.componentDidMount.bind(this);
        this.itemClicked = this.itemClicked.bind(this);
        this.makeItems = this.makeItems.bind(this);
    }

    itemClicked(selected) {
        this.props.itemClicked(selected);
    }

    makeItems() {
        if(this.state.code == "")
            return;
        const eyss = this.state.eyss;
        const code = this.state.code.toString();
        var items = eyss.map(eys => "")
                        .join(",,")
                        .split(',');

        items = items.map(function(str,i) {
            if(i%2 == 0) {
                const eys = eyss[Math.floor(i/2)];
                const selected = this.props.selected;
                return <ParserCodeDivItem key = {eys.id} eys={eys} itemClicked = {this.itemClicked} selected = {selected}/>
            }
            else{
                var l = eyss[Math.floor(i/2)].r;
                var r = eyss[Math.floor(i/2) + 1].l;
                return code.substring(l,r);
            }
        },this);

        items.unshift(code.substring(0, eyss[0].l));
        items.push(code.substring(eyss[eyss.length - 1].r, code.length));

        return items;
    }

    componentDidMount(){
        ajax.get('/compiler/jsonFiles/parseAns.json')
            .end((err, res)=>{
                this.setState({
                    eyss: JSON.parse(res.text)
                });
            });
        
        ajax.get('/compiler/source/code.source')
            .end((err, res) =>{
                this.setState({
                    code: res.text
                });
            });
    }

    render() {
        var items = this.makeItems();

        return (
            <div id="code_dev" className="view_item">\
                <center><h2 id="table_name">源码</h2></center>
                <pre>
                    {items}
                </pre>
            </div>
        );
    }
}