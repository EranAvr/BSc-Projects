const express = require('express');
const router = express.Router();

 // router is a middleware, used for handling 
 // dynamic addresses (addresses that contain parameters)
router.get('/', (req, res) => {
    res.send('<html><body><h2>Welcome Guest</h2><h3>Enter name to login</h3></body></html>');
});
router.get('/:name', (req, res) => {
    // We define a variable in the address,
    // by adding ':'+<var name> for a variable.
    res.send("<html><body><h1>Hello User "+req.params.name+" </h1></body></html>");
    // After defining a variable, we can access
    // it with 'req.params.<var name>'.
});

module.exports = router;