class EssayForm extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            value:`
const a=10;
var b,c;
procedure p;
begin
  c:=b+a
end;
begin
  read(b);
  if c=b then c := 1;
  while b#0 do
    begin
      call  p;
      write(2*c);
      read(b);
    end
end.
            `
        };

        this.handleChange = this.handleChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }

    handleChange(event){
        this.setState({value: event.target.value});
    }

    handleSubmit(event){

    }

    render(){
        return(
            <form onSubmit = {this.handleSubmit} method="post">
                文章:
                <textarea value={this.state.value} onChange = {this.handleChange} name = "code"/>
                <input type = "submit" value="提交" />
            </form>
        );
    }
}


ReactDOM.render(
    <EssayForm/>,
    document.getElementById('example')
);