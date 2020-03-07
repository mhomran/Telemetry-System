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


@app.route("/hello", methods=['GET'])
def hello():
    return "hello"

@app.route("/json", methods=["POST"])
def json_example():

    if request.json:
        req = request.get_json()
        response_body = {
            "message": "JSON received!",
            "sender": req.get("Name")
        }
        res = make_response(jsonify(response_body), 200)
        return res
    else:
        return make_response(jsonify({"message": "Request body must be JSON"}), 400)

@app.route("/", methods=['GET'])
def student():
    return render_template("index.html")


# for CORS
flask_cors.CORS(app)

# debug is for restarting whenever app.py changes
app.run(debug=True, port=8081)

