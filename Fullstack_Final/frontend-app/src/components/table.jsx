import React, {Component} from "react";

class MyTable extends Component {

    constructor(props) {
        super(props);
        this.state = {
            title: this.props.title,
            users: [],
        }
        //this.setState({users: this.props.users})
    }

    render() {
        return(
            <div className="border border-light rounded-2 pb-3 mb-5" style={{backgroundColor: "#aeaeae"}}>
                <div className="d-flex justify-content-center">
                <h2 className="my-3">{this.state.title}</h2>
                </div>
                <div className="d-flex justify-content-center">
                <table className="table">
                    <thead className="thead-dark">
                    <tr>
                        <th>#</th>
                        <th>username</th>
                        <th>full-name</th>
                        <th>email</th>
                        <th>uid</th>
                    </tr>
                    </thead>
                    {this.loadUsers()}
                </table>
                </div>
            </div>
        );
    }
    loadUsers() {
        console.log("loadUsers() called");
        const currentUsers = this.props.users;
        console.log(currentUsers.map(()=>'item'));
        var counter = 1;
        return(
            <React.Fragment>
                <tbody>
                  {currentUsers.map(usr => 
                        <tr className="list-group-item-action"
                        onClick={() => this.props.onRowClick(usr.uid)}>
                          <th>{counter++}</th>
                          <td>{usr.userName}</td>
                          <td>{usr.fullName}</td>
                          <td>{usr.email}</td>
                          <td>{usr.uid}</td>
                        </tr>
                    )}
                </tbody>
            </React.Fragment>
        );
    }
}

export default MyTable;