
document.addEventListener("DOMContentLoaded", event => {
    const app = firebase.app();
    var database = firebase.database();
        firebase.database().ref('users/' + '').set({
     username: "Toqa",
      email: "toka.eldoghamy1@gmail.com",
      profile_picture : ""
    });
});


