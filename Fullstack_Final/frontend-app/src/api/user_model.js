import { v4 as uuidv4 } from 'uuid';

class UserModel {
    constructor(userName, password, email, fullName='', role='user', pic='') {
        this.uid = uuidv4();
        this.userName = userName;
        this.password = password;
        this.email = email;
        this.fullName = fullName;
        
        this.role = role;
        this.picture = pic;
    }

    toJSON() {
        return {
            uid: this.uid,
            userName: this.userName,
            password: this.password,
            email: this.email,
            role: this.role,
            fullName: this.fullName,
            picture: this.pic,
        };
    }
}

export default UserModel;