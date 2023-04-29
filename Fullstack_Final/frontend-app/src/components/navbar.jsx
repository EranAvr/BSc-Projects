import React, {Component} from "react";
import { FaReact } from 'react-icons/fa';
import { Link } from "react-router-dom";

class Navbar extends Component {
    constructor(props) {
        super(props);
        this.state = {};
    }
    
    // methods:
    render() {
        return(
            <nav className="navbar navbar-expand-lg navbar-light justify-content-between"
            style={{backgroundColor: "#384b59"}}>
                <div className="d-flex align-items-start ms-3">
                    <Link className="navbar-brand" to='/'>
                        <FaReact />
                    </Link>
                    <div className="navbar-nav align-self-start">
                        <Link className="nav-link active" to='/dashboard'>Dashboard</Link>
                    </div>
                    <div className="navbar-nav">
                        <Link className="nav-link" to='/about'>About</Link>
                    </div>
                    <div className="navbar-nav">
                        <Link className="nav-link" to='/contact'>Contact</Link>
                    </div>
                </div>
                {this.genLoginLink()}
            </nav>
        )
    }

    genLoginLink() {
        if(this.props.loggedUser['userName']){
            return(<React.Fragment>
                <div className="navbar-nav me-3">
                    <h3 className="nav-text">Welcome {this.props.loggedUser['userName']}</h3>
                </div>
                <div className="navbar-nav me-3">
                    <span className="nav-text">Logged in</span>
                </div>
            </React.Fragment>
            
            );
        }
        else {
            return(
                <div className="navbar-nav me-3">
                    <Link className="nav-link active" to='/login_card'>Login</Link>
                </div>
            );
        }
    }
  };

export default Navbar;