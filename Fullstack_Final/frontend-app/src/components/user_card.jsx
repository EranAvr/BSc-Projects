import React, { Component } from 'react';

class UserCard extends Component {

  constructor(props) {
    super(props);
    this.state = {
        pic: "https://www.planetware.com/wpimages/2020/02/france-in-pictures-beautiful-places-to-photograph-eiffel-tower.jpg",
      };
  }
  

  render() {
    const user = this.props.user;
    return (
      <div className="card" style={{width: "400px" }}>
        <div className="row text-center my-3">
          <h5 className="card-title">User Card</h5>
        </div>
        <div className="row crad-body text-center">
          <div className="col-6 px-3">
            <ul className="card-text list-group list-group-flush">
              <li className="list-group-item">
                <label>{user.userName}</label>
                <span></span>
              </li>
              <li className="list-group-item">
                <label>{user.role}</label>
                <span></span>
              </li>
            </ul>
          </div>
          <div className="col-6 g-0 d-flex justify-content-center">
            <img
              className="card-img-right rounded-circle"
              style={{ maxWidth: "150px" }}
              src={this.state.pic}
              alt="logo image"
            />
          </div>
        </div>
        <div className="row crad-body p-3 text-start">
          <div className="col">
            <ul className="card-text list-group list-group-flush">
              <li className="list-group-item">
                <label className="float-start">UID:</label>
                <span className="float-end">{user.uid}</span>
              </li>
              <li className="list-group-item">
                <label className="float-start">Full Name:</label>
                <span className="float-end">{user.fullName}</span>
              </li>
              <li className="list-group-item">
                <label className="float-start">Email:</label>
                <span className="float-end">{user.email}</span>
              </li>
            </ul>
          </div>
        </div>
      </div>
    );
  }
}

export default UserCard;
