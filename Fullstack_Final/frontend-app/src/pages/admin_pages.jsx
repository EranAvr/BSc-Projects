import React, { Component, useState } from "react";
import UserCard from "../components/user_card";
import MyTable from "../components/table";
import PostCard from "../components/post_card";

export class AdminHome extends Component {
  constructor(props) {
    super(props);
    this.state = {
      notifyCardsList: [this.renderNotifyCard(),
        this.renderNotifyCard(),
        this.renderNotifyCard()
      ],
    };
  }

  render() {
    return (
      <div className="container">
        <h1 className="my-4 text-center">Admin Home Panel</h1>
        <h2>News and Updates</h2>
        <div className="row my-4">
          <div className="col d-flex">
            {this.state.notifyCardsList}
          </div>
        </div>
        <div className="row my-4">
          <h2>Home extra content</h2>
          <p>
            Lorem ipsum dolor sit amet consectetur adipisicing elit.
            <br />
            Quibusdam, pariatur inventore. Sint, dolore commodi.
            <br />
            Iste sit consectetur porro, sed, aspernatur at,
            <br />
            architecto magni vero quis ad libero eos consequatur dolor?
          </p>
        </div>
      </div>
    );
  }

  renderNotifyCard = () => {
    return(
      <div className="card me-3" style={{ width: "150px" }}>
              <div className="card-body">
                <h5 className="card-title text-center">Card Title</h5>
                <h6 className="card-subtitle text-center text-muted">
                  Card Subtitle
                </h6>
                <p className="card-text mt-2">
                  Some text to present to the user..
                </p>
                <a className="card-link" href="#">
                  dismiss
                </a>
              </div>
            </div>
    );
  }
  dismissNotifyCard = id => {
  }
}

export class AdminInfo extends Component {

  constructor(props) {
    super(props);

  }

  render() {
    return (
      <div className="container-fluid d-flex justify-content-center pt-3">
        <UserCard user={this.props.user} />
      </div>
    );
  }
}

export class UsersPanel extends Component {
  constructor(props) {
    super(props);
    this.state = {
      usersList: [],
      adminsList: [],
    };
  }

  componentDidMount(){
    this.fetchUsers();
    this.fetchAdmins();
  }

  render() {
    return (
      <div className="container">
        <h1 className="my-4 text-center">Users Panel</h1>
        <div className="row my-3">
          <form onSubmit={this.handleOnSubmit} className="border border-light rounded-2">
            <div className="row">
              <div className="col-4">
                <div className="form-group">
                  <input
                    id="input_txt_name"
                    className="form-control my-2"
                    type="text"
                    placeholder="enter username"
                  ></input>
                  <input
                    id="input_txt_pass"
                    className="form-control my-2"
                    type="text"
                    placeholder="enter password"
                  ></input>
                  <input
                    id="input_txt_pass_auth"
                    className="form-control my-2"
                    type="text"
                    placeholder="enter password again"
                  ></input>
                </div>
                <div className="form-group">
                  <input
                    id="input_txt_full_name"
                    className="form-control my-2"
                    type="text"
                    placeholder="enter full name"
                  ></input>
                  <input
                    id="input_txt_email"
                    className="form-control my-2"
                    type="email"
                    placeholder="enter email"
                  ></input>
                </div>
              </div>
              <div className="col-8">
                <textarea
                  id="input_txt_freetxt"
                  className="form-control mt-2 h-75"
                  placeholder="enter free text.."
                ></textarea>
              </div>
            </div>
            <div class="dropdown-divider"></div>
            <div className="col d-flex justify-content-evenly my-3">
              <input
                id="input_btn_clear"
                className="btn btn-primary"
                type="button"
                value="Clear"
              ></input>
              <input
                id="input_btn_submit"
                className="btn btn-primary"
                type="submit"
                value="Submit"
              ></input>
            </div>
          </form>
        </div>

        <div className="row my-3">
          <div className="col-11 ">
            <MyTable title='All Admins' users={this.state.adminsList} onRowClick={this.rowClickHandler}/>
            <MyTable title='All Users' users={this.state.usersList} onRowClick={this.rowClickHandler}/>
          </div >
          
          <div id="id_sticky_menu"
            className="col-1 sticky-top text-center border border-light rounded-2 bg-warning"
            style={{ height: "150px" }}>
            <p>
              <b>options</b>
            </p>
            <p>
              <a className="card-link" href="#">
                delete
              </a>
            </p>
            <p>
              <a className="card-link" href="#">
                option2
              </a>
            </p>
            <p>
              <a className="card-link" href="#">
                option3
              </a>
            </p>
          </div>
        </div>
      </div>
    );
  }

  rowClickHandler = (uid) => {
    alert('User ID: '+uid);
  }
  presentUser = async (uid) => {

  }

  fetchUsers = async () => {
    const requestOptions = {
      method: 'GET'
    };
    const response = await fetch('http://localhost:8000/users/getAll/'+'user', requestOptions);
    const users = await response.json();
    this.setState({usersList: users});
  }
  fetchAdmins = async () => {
    const requestOptions = {
      method: 'GET'
    };
    const response = await fetch('http://localhost:8000/users/getAll/'+'admin', requestOptions);
    const users = await response.json();
    this.setState({adminsList: users});
  }

  createUsersTable() {
    this.fetchUsersList();
    return(
        <React.Fragment>
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
                <tbody>
                  {
                    this.state.usersList.map(usr => {
                        <tr>
                          <th>1</th>
                          <td>{usr.userName}</td>
                          <td>{usr.fullName}</td>
                          <td>{usr.email}</td>
                          <td>{usr.uid}</td>
                        </tr>
                    })
                  }
                </tbody>
            </table>
        </React.Fragment>
        
    );
  }
}

export class PostsPanel extends Component {
  constructor(props) {
    super(props);
    this.state = {
      currentUid: this.props.user.uid,
      postsList: [],
      postsCount: () => {
          return this.state.posts.length;
      },
    };
  }

  componentDidMount() {
    this.fetchUserPosts();
  }

  render() {
    return (
      <div className="container">
        <h1 className="my-4 text-center">All Users Posts</h1>
        <div className="col my-3">
          {this.renderPostcards()}
        </div>
      </div>
    );
  }

  renderPostcards() {
    console.log(this.state.postsList);
    const postcards = this.state.postsList.map(_postObj => <PostCard data={_postObj} />);
    return(postcards);
  }

  fetchUserPosts = async () => {
    const requestOptions = {
      method: 'GET'
    };
    const response = await fetch('http://localhost:8000/posts/getAll/', requestOptions);
    const posts = await response.json();
    this.setState({postsList: posts});
  }


  alternativeCard() {
    return(
      <div className="card m-3">
            <div className="card-body">
              <h4 className="card-title text-end">#1</h4>
              <h4 className="card-title">Card Title</h4>
              <h6 className="card-subtitle">Some declerative subtitle..</h6>
              <p className="card-text mt-2">
                Lorem ipsum dolor sit amet consectetur adipisicing elit. Velit
                officia enim ad minima maiores numquam temporibus rerum dolorum?
                Quam optio similique reiciendis fugiat facere placeat aut
                voluptatum? Alias, magnam dolores.
              </p>
              <a className="card-link" href="">
                react
              </a>
              <a className="card-link" href="">
                dismiss
              </a>
            </div>
      </div>
    );
  }
}
