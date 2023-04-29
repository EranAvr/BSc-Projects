const express = require('express');
const router = express.Router();
const db = require('../mongoDB_api');
const COLLECTION_NAME = "posts";

// ----------------------------- GET ----------------------------------------
router.get('/', (req, res) => {
    res.send('Posts main endpoint');
});
router.get('/getByTitle/:title', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({title: req.params.title}).toArray();
    res.send(results);
});
router.get('/getByPid/:pid', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.findOne({pid: req.params.pid}).toArray();
    res.send(result);
});
router.get('/getByUid/:uid', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({uid: req.params.uid}).toArray();
    res.send(results);
});
router.get('/getAll', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const results = await collection.find({}).toArray();
    res.send(results);
});

// ----------------------------- POST ----------------------------------------
router.post('/submit', async (req, res) => {
    const collection = await db.collection(COLLECTION_NAME);
    const newDocument = req.body;
    const result = collection.insertOne(newDocument, (err, result)=>{
        if (err) throw err;
    });
    res.send(result);
});

// ----------------------------- PATCH ----------------------------------------
router.patch('/update/:pid', async (req, res) => {
    const queryObj = {pid: req.params.pid};
    const updates = {
        $set: {"title": req.body.title,
        "text": req.body.text,
        "bgColor": req.body.bgColor,
        "timeStamp": req.body.timeStamp}
    };
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.updateOne(queryObj, updates);
    res.send(result);
});

// ----------------------------- DELETE ----------------------------------------
router.delete('/deleteOne/:pid', async (req, res) => {
    const queryObj = {pid: req.params.pid};
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.deleteOne(queryObj);
    res.send(result);
});
router.delete('/deleteMany/:uid', async (req, res) => {
    const queryObj = {uid: req.params.uid};
    const collection = await db.collection(COLLECTION_NAME);
    const result = await collection.deleteMany(queryObj);
    res.send(result);
});


module.exports = router;