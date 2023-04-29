import { v4 as uuidv4 } from 'uuid';

class PostModel {
    constructor(uid, title, text, bgColor='') {
        this.pid = uuidv4();
        this.uid = uid;
        this.title = title;
        this.text = text;
        this.timeStamp = Date.now();
        this.bgColor = bgColor;
    }

    toJSON() {
        return {
            pid: this.pid,
            uid: this.uid,
            title: this.title,
            text: this.text,
            timeStamp: this.timeStamp,
            bgColor: this.bgColor,
        }
    }
}

export default PostModel;