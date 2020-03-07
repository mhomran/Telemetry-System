from flask import Flask, render_template, request, jsonify, make_response
import flask_cors
import json

app = Flask(__name__, static_folder='assets')


@app.route("/readjsonfile", methods=['GET'])
def read_json_file():
    # read json file
    F = open("labs/write_file.json", "r")
    # turn the data into dictionary
    data_store = json.load(F)
    js_object = make_response(jsonify(data_store), 200)
    return js_object


# making json file
@app.route("/writejsonfile", methods=['POST'])
def write_json_file():
    write_file = open("labs/write_file.json", "w")
    if request.json:
        req = request.get_json()
        json.dump(req, write_file)

    return "Saved"

# for CORS
flask_cors.CORS(app)

# debug is for restarting whenever app.py changes
app.run(debug=True, port=8081)

