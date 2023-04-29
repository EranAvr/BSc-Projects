const { MongoClient } = require("mongodb");

const LOCAL_HOST = "0.0.0.0";
const DB_NAME = "final_project";
const URI = "mongodb://" + LOCAL_HOST + ":27017"; // Connection URI

const client = new MongoClient(URI, {
  useUnifiedTopology: true,
  useNewUrlParser: true,
});

client.connect();
const db = client.db(DB_NAME);

module.exports = db;

/*
async function createPost(_reqBody) {
    const client = new MongoClient(URI);
    try{
        await client.connect();
        await client.db(DB_NAME).command({ping: 1});
        const db = client.db(DB_NAME);
        console.log('Connected successfuly to DB: ' + DB_NAME);

        const myColl = db.collection(COLLECTIONS.posts);
        const result = await myColl.insertOne(_reqBody, (err, result)=>{
            if (err) throw err;
            console.log(result);
        });
        console.log('Inserted item _id=' + result.insertedId);
    }
    finally{
        await client.close();
        console.log('Disconnected from DB: ' + DB_NAME);
    }
}

async function updatePost(_pid, _title, _post_txt) {
    console.log('createPost() params: '+_title+' '+_post_txt);
            const client = new MongoClient(URI);
    try{
        await client.connect();
        await client.db(DB_NAME).command({ping: 1});
        const db = client.db(DB_NAME);
        console.log('Connected successfuly to DB: ' + DB_NAME);

        const myColl = db.collection(COLLECTIONS.posts);
        const result = await myColl.findOneAndUpdate({_id: _pid}, (err, result)=>{
            if (err) throw err;
            console.log(result);
        });
        console.log('Updated item _id=' + result.insertedId);
    }
    finally{
        await client.close();
        console.log('Disconnected from DB: ' + DB_NAME);
    }
}

async function deletePost(_pid) {
    console.log('createPost() params: '+_title+' '+_post_txt);
    const client = new MongoClient(URI);
    try{
        await client.connect();
        await client.db(DB_NAME).command({ping: 1});
        const db = client.db(DB_NAME);
        console.log('Connected successfuly to DB: ' + DB_NAME);

        const myColl = db.collection(COLLECTIONS.posts);
        const result = await myColl.findOneAndDelete({_id: _pid}, (err, result)=>{
            if (err) throw err;
            console.log(result);
        });
        console.log('Deleted item _id=' + result.insertedId);
    }
    finally{
        await client.close();
        console.log('Disconnected from DB: ' + DB_NAME);
    }
}

async function createUser() {
    try {
        const client = new MongoClient(URI);
        await client.connect();
        await client.db(DB_NAME).command({ping: 1});
        const db = await client.db(DB_NAME);
        console.log('>> Connected successfuly to DB: ' + DB_NAME);

        await db.addUser("UserName1", "password1",
         {roles: [{role: "readWrite" , db: DB_NAME}]}, (err, result)=>{
            if (err) throw err;
            console.log('User created');
         });
    }
    catch(error) {
        console.error('>> Error Catch:\n'+error);
    }
    finally {
        await client.close();
        console.log('>> Disconnected from DB: ' + DB_NAME);
    }
}
async function createAdmin() {
    try {
        const client = new MongoClient(URI);
        await client.connect();
        await client.db(DB_NAME).command({ping: 1});
        const db = await client.db(DB_NAME);
        console.log('>> Connected successfuly to DB: ' + DB_NAME);

        await db.addUser("Eran", "0000",
         {roles: [{role: "userAdminAnyDatabase" , db: 'admin'}]}, (err, result)=>{
            if (err) throw err;
            console.log('Admin created');
         });
    }
    catch(error) {
        console.error('>> Error Catch:\n'+error);
    }
    finally {
        await client.close();
        console.log('>> Disconnected from DB: ' + DB_NAME);
    }
}

//createPost('some title', 'some post text');
module.exports = { createPost, updatePost, deletePost };
*/
