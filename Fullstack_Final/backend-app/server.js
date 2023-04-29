const express = require('express');     // Node-JS module for internet server
const cors = require('cors');   // security package for cross-origin-reasource-sharing
const usersRouter = require('./my-routers/users_router');    // import our custom router middleware
const postsRouter = require('./my-routers/posts_router');
const app = express();
const PORT = 8000;

app.use(cors())  ;   // add a middleware to our app
app.use(express.urlencoded({ extended: true }));    // parse requests of content-type - application/x-www-form-urlencoded
app.use(express.json());   // parse incoming requests with built-in func json()
//app.use(bodyParser.urlencoded({ extended: true }));
//app.use(bodyParser.json());

// Create a response for main endpoint,
// we use json() method to return a JSON object.
app.get('/', (req, res) => {
    res.json({"main": "My-Server main endpoint"});
});


app.use('/users', usersRouter);   // route our middleware to route '/user/..'
app.use('/posts', postsRouter);
app.use(express.static('public')); // define static router

app.listen(PORT, () => {
    // This callback executes once the server
    // starts on listening to the provided port.
    console.log("Express Server is running on port 8000");
})

