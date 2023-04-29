import "./App.css";
import React, {Component} from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Navbar from "./components/navbar";
import Footer from "./components/footer";

import LoginCard from "./components/login_card";
import SignupCard from "./components/signup_card";
import DashboardAdmin from "./pages/dashboard_admin";
import DashboardUser from "./pages/dashboard_user";
import Home from "./pages/home";
import About from "./pages/about";
import Contact from "./pages/contact";
import NoPage from "./pages/no_page";
import { AdminHome, AdminInfo, UsersPanel, PostsPanel } from "./pages/admin_pages";
import { UserInfo, UserPosts, UserWritePost } from "./pages/user_pages";
import { useState } from "react";

function App() {
  // Here, we define our main-page
  // structure and components.
  const [loggedUser, setLoggedUser] = useState({});

  const myLoginCallBack = (user) => {setLoggedUser(user)};

  return (
    <BrowserRouter>
      <Navbar loggedUser={loggedUser}/>

      <div className="d-flex min-vh-100">
        <Routes>
          <Route exact path="/" element={<Home />}></Route>
          <Route path="/login_card" element={<LoginCard handleLogin={myLoginCallBack}/>}></Route>
          <Route path="/signup_card" element={<SignupCard />}></Route>
          <Route path="/about" element={<About />}></Route>
          <Route path="/contact" element={<Contact />}></Route>
          {genUserRoutes(loggedUser)}
          <Route path="*" element={<NoPage />}></Route>
        </Routes>
      </div>

      <Footer />
    </BrowserRouter>
  );
}

function genUserRoutes(user) {
  // check if user is admin
  if (user.role === 'admin') {
    return (
      <Route exact path="/dashboard" element={<DashboardAdmin />}>
        <Route path="dash_home" element={<AdminHome user={user} />} />
        <Route path="my_info" element={<AdminInfo user={user} />} />
        <Route path="dash_users" element={<UsersPanel user={user} />} />
        <Route path="dash_updates" element={<PostsPanel user={user} />} />
        <Route path="*" element={<NoPage />} />
      </Route>
    );
  }
  else if(user.role === 'user') {
    return (
      <Route exact path="/dashboard" element={<DashboardUser />}>
        <Route path="my_info" element={<UserInfo user={user} />} />
        <Route path="my_posts" element={<UserPosts user={user} />} />
        <Route path="write_update" element={<UserWritePost user={user} />} />
        <Route path="*" element={<NoPage />} />
      </Route>
    );
  }
  else {
    
  }
}

export default App;
