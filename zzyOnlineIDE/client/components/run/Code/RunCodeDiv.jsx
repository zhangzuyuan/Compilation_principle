import RunCodeDivItem from './RunCodeDivItem.jsx';

import './RunCodeDiv.css'

export default class RunCodeDiv extends React.Component {
    constructor(props){
        super(props);
    }

    render() {
        let codes = this.props.state.codes;
        let P =this.props.state.P;
        let codeDivItems = codes.map(function (code) {
            return (
                <RunCodeDivItem key={code.id} code={`${code.f} ${code.l} ${code.a}`} selected={P === code.id} />
            );
        });

        return (
            <div className="view_item code_div">
                <table className="code_table">
                    <tbody>
                        <tr>
                            <th></th>
                            <th>code</th>
                        </tr>
                        {codeDivItems}
                    </tbody>
                </table>
            </div>
        )
    }
}