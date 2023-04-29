const express = require('express');
const router = express.Router();
const db = require('../mongoDB_api');
const COLLECTION_NAME = "users";

// ----------------------------- GET ----------------------------------------
router.get('/', (req, res) => {
    res.send('Users main endpoint');
});
router.get('/getByUid/:uid', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.findOne({uid: req.params.uid});
    res.send(result);
});
router.get('/getByUserName/:userName', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.findOne({userName: req.params.userName});
    res.send(result);
});
router.get('/getByFullName/:fullName', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.findOne({fullName: req.params.fullName});
    res.send(result);
});
router.get('/getByRole/:role', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({role: req.params.role}).toArray();
    res.send(results);
});
router.get('/getByEmail/:email', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({email: req.params.email}).toArray();
    res.send(results);
});
router.get('/getAll/:user', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({role: req.params.user}).toArray();
    res.send(results);
});
router.get('/getAll', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({}).toArray();
    res.send(results);
});

// ----------------------------- POST ----------------------------------------
router.post('/signup', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const newDocument = req.body;
    const result = collection.insertOne(newDocument, (err, result)=>{
        if (err) throw err;
    });
    res.send(result);
});
router.post('/login', async (req, res) => {
    //const queryObj = { $and: [{userName: req.body.userName}, {password: req.body.password}]};
    const queryObj = {userName: req.body.userName, password: req.body.password};
    const optionsObj = {_id: 0, password: 0};
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.findOne(queryObj, optionsObj);
    if (!result) {
        res.status(404).send(result);
    }
    else {
        res.status(200).send(result);
    }
});

// ----------------------------- PATCH ----------------------------------------
router.patch('/updateByUid/:uid', async (req, res) => {
    const queryObj = {uid: req.params.uid};
    const optionsObj = {_id: 0};
    const collection = await db.collection(COLLECTION_NAME);
    const checkUser = await collection.findOne(queryObj, optionsObj);
    const fields = {userName: "userName",
        role: "role",
        fullName: "fullName",
        email: "email",
        picture: "pic"
    };
    for(var k in fields) {
        fields[k] = (k in req.body ? req.body[k] : checkUser[k] );
    }
    updates = {
        $set: fields
    };
    
    const result = await collection.updateOne(queryObj, updates);
    res.send(result);
});
router.patch('/updateByUN/:userName', async (req, res) => {
    const queryObj = {userName: req.params.userName};
    const optionsObj = {_id: 0};
    const collection = await db.collection(COLLECTION_NAME);
    const checkUser = await collection.findOne(queryObj, optionsObj);
    const fields = {userName: "userName",
        role: "role",
        fullName: "fullName",
        email: "email",
        picture: "pic"
    };
    for(var k in fields) {
        fields[k] = (k in req.body ? req.body[k] : checkUser[k] );
    }
    updates = {
        $set: fields
    };

    const result = await collection.updateOne(queryObj, updates);
    res.send(result);
});

// ----------------------------- DELETE ----------------------------------------
router.delete('/deleteByUid/:uid', async (req, res) => {
    const queryObj = {uid: req.params.uid};
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.deleteOne(queryObj);
    res.send(result);
});
router.delete('/deleteByRole/:role', async (req, res) => {
    const queryObj = {role: req.params.role};
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.deleteMany(queryObj);
    res.send(result);
});
router.delete('/deleteByEmail/:email', async (req, res) => {
    const queryObj = {email: req.params.email};
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.deleteMany(queryObj);
    res.send(result);
});


module.exports = router;