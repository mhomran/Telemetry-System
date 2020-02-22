var Speed = 0;
var Current = 0;

document.addEventListener("DOMContentLoaded", event => {
    const app = firebase.app();
    console.log(app);
    var database = firebase.database();
    firebase.database().ref('users/' + '').set({
      username: "Toqa",
      email: "toka.eldoghamy1@gmail.com",
      profile_picture : ""
    });
    //var dbRef = firebase.database().ref('Data');
    
}
);

