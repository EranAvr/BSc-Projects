import React, { Component } from "react";
import UserCard from "../components/user_card";
import PostCard from "../components/post_card";
import PostModel from '../api/post_model';

export class UserInfo extends Component {

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

export class UserPosts extends Component {

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
        <h1 className="my-4">User Posts</h1>
        <ul class="list-group list-group-flush">
          {this.renderPostcards()}
        </ul>
      </div>
    );
  }

  renderPostcards() {
    const postcards = this.state.postsList.map(_postObj => <PostCard data={_postObj} />);
    return(postcards);
  }

  fetchUserPosts = async () => {
    const requestOptions = {
      method: 'GET'
    };
    const response = await fetch('http://localhost:8000/posts/getByUid/'+this.state.currentUid, requestOptions);
    const posts = await response.json();
    this.setState({postsList: posts});
  }
}

export class UserWritePost extends Component {

  constructor(props) {
    super(props);
    this.state = {
      currentUid: this.props.user.uid,
      title: "",
      text: "",
      color: "",
    }

  }
  render() {
    return (
      <div className="container-fluid">
        <div className="row text-center">
          <h1 className="my-4">Write New Post</h1>
        </div>
        <div className="row">
          <div className="col-2 d-flex flex-column align-items-center">
            <button onClick={this.handleSubmit} className="btn btn-success">Submit</button>
          </div>

          <div className="col-10 d-flex flex-column">
            <input id="id_newpost_title" className="form-control mb-2" placeholder="post title"
            onChange={({target})=>{this.setState({title: target.value})}} />
            <textarea
              className="form-control h-75 mb-2"
              name="user_new_post"
              id="id_newpost_textarea"
              cols="30"
              rows="10"
              placeholder="post text"
              onChange={({target})=>{this.setState({text: target.value})}}
            ></textarea>
            <input
              id="id_newpost_color"
              type="color"
              className="form-control form-control-color"
              placeholder="post title"
              onChange={({target})=>{this.setState({color: target.value})}}
            />
          </div>
        </div>
      </div>
    );
  }

  fieldsNotEmpty = () => {
    const state = this.state;
    return state.title !== "" 
    && state.text !== "";
}
  handleSubmit = () => {
        const state = this.state;
        if(this.fieldsNotEmpty()) {
            const post = new PostModel(state.currentUid, state.title, state.text, state.color);
            const requestOptions = {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(post.toJSON())
            };
            fetch('http://localhost:8000/posts/submit', requestOptions)
            .then((response) => {response.json()})
            .then(data => {console.log(data)});
        }
        else {

        }
  }
}
