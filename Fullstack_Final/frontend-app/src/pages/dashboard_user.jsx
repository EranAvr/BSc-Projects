import React, {Component} from 'react';
import { Outlet, Link } from 'react-router-dom';

class DashboardUser extends Component {
    
    state = {
        paths: ["dash_home", "dash_users", "dash_updates"]
    };

    render(){
        return(
            <div className='container-fluid row'>
                <div className='col-2 vh-100 bg-secondary justify-content-center'>
                    <nav className='d-flex align-items-start navbar navbar-light bg-secondary justify-content-center'>
                        <Link to='my_info'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center'>
                        <h5 className='text-dark'>My Info</h5>
                        </Link>
                        <Link to='my_posts'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center'>
                        <h5 className='text-dark'>My Posts</h5>
                        </Link>
                        <Link to='write_update'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center'>
                        <h5 className='text-dark'>New Post</h5>
                        </Link>
                    </nav>
                </div>
                <div className='col-10 vh-100 justify-content-center overflow-auto'>
                    <Outlet/>
                </div>
        </div>);
    }
};

export default DashboardUser;