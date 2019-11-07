var Speed = 0;
document.addEventListener("DOMContentLoaded", event => {
    const app = firebase.app();
    console.log(app);

    
    var dbRef = firebase.database().ref().child('Measure/Speed');
    dbRef.on('value', snap => Speed = snap.val());
}
);

