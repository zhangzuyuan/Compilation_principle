import ajax from '../../../lib/superagent';

import EysDivItem from './EysDivItem.jsx';

import './EysDiv.css';

export default class EysDiv extends React.Component{
    constructor(props){
        super(props);

        this.state = {eyss: []};

        this.itemClicked = this.itemClicked.bind(this);
    }

    itemClicked(selected) {
        this.props.itemClicked(selected);
    }

    componentDidMount(){
        ajax.get('/compiler/jsonFiles/lexicalAns.json')
            .end((err,res)=>{
                this.setState({
                    eyss: JSON.parse(res.text)
                });
            });
    }

    render(){
        const eyss = this.state.eyss;
        const selected = this.props.selected;
        const itemClick = this.itemClicked;
        const eysDivItems = eyss.map(function(eys){
            return(
                <EysDivItem key={eys.id} itemClicked={itemClick} selected={selected} eys={eys}/>
            );
        });

        return(
            <div id="eys_div" className = "view_item">
                <center><h2 id="table_name">二元式</h2></center>
                <table border="1" className="eys_table">
                    <tbody>
                        <tr>
                            <th>序号</th>
                            <th>内容</th>
                            <th>类型</th>
                            <th>编号</th>
                        </tr>
                        {eysDivItems}
                    </tbody>
                </table>
            </div>
        )
    }
}