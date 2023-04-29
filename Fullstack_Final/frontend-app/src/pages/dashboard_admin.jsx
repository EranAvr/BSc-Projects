import React, {Component} from 'react';
import { Outlet, Link } from 'react-router-dom';

class DashboardAdmin extends Component {
    
    state = {
        paths: ["dash_home", "dash_users", "dash_updates"]
    };

    render(){
        return(
            <div className='container-fluid row'>
                <div className='col-2 vh-100 bg-secondary justify-content-center'>
                    <nav className='d-flex align-items-start navbar navbar-light bg-secondary justify-content-center'>
                        <Link to='dash_home'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center list-group-item-action'>
                            <h5 className='text-dark'>Admin Home</h5>
                        </Link>
                        <Link to='my_info'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center list-group-item-action'>
                        <h5 className='text-dark'>My Info</h5>
                        </Link>
                        <Link to='dash_users'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center list-group-item-action'>
                            <h5 className='text-dark'>Users</h5>
                        </Link>
                        <Link to='dash_updates'
                        className='container py-3 m-2 border border-2 rounded-3 border-dark justify-content-center list-group-item-action'>
                            <h5 className='text-dark'>Users Posts</h5>
                        </Link>
                    </nav>
                </div>
                <div className='col-10 vh-100 justify-content-center overflow-auto'>
                    <Outlet/>
                </div>
        </div>);
    }
};

export default DashboardAdmin;