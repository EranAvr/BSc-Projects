import React, { Component } from "react";

class PostCard extends Component {
    constructor(props) {
        super(props);
    }
    state = {
        currentPost: this.props.data,
    };

    render() {
        const post = this.state.currentPost;
        return (
            <div className="card mb-5">
                <div className="card-header text-center">
                    <span id="postcard_header">{post.uid}</span>
                </div>
                <div className="crad-body text-start my-1" style={{backgroundColor: post.bgColor}}>
                    <h5 id="postcard_title" className="card-title">{post.title}</h5>
                    <p id="postcard_text" className="card-text">
                        {post.text}
                    </p>
                </div>
                <div id="postcard_footer" className="card-footer text-muted text-center">
                    <span id="postcard_header">{""+new Date(post.timeStamp)}</span>
                </div>
            </div>
        );
    }
}

export default PostCard;
