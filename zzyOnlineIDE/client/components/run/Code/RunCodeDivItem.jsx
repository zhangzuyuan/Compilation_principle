export default class RunCodeDivItem extends React.Component{
    constructor(props) {
        super(props);
    }

    render() {
        let selected = "";
        if (this.props.selected)
            selected = "→";
        return (
            <tr>
                <th>{selected}</th>
                <th>{this.props.code}</th>
            </tr>
        );
    }
}