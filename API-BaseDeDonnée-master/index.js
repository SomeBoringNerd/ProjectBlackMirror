const express = require("express");
const sqlite3 = require('sqlite3').verbose();
const bodyParser = require("body-parser");

const api = express();

api.use(bodyParser.urlencoded({ extended: false }));
api.use(bodyParser.json());

let db;

api.listen(1984, () => 
{
    LogPropre("l'api a été chargée sur le port 1984");
    db  = new sqlite3.Database('./Profs.db', sqlite3.OPEN_READWRITE);
    
    //                                                              plaque est primary      vrai ou     si c'est un
    //                                                                  key                 faux        compte temporaire
    //db.run("CREATE TABLE Profs (NOM VARCHAR(64), PRENOM VARCHAR(64), PLAQUE VARCHAR(12), PROF TINYINT, EXPIRATION DATE)")
})

api.post("/get", (req, rep) => {
    if(req.query.plaque === undefined)
    {
        let json = {
            returnCode: 403,
            message: "absence de plaque dans methode POST"
        }

        rep.json(json);
    }else{
        db.each(`SELECT * FROM Profs WHERE PLAQUE="${cleanInputs(req.query.plaque)}"`, (err, row) => 
        {

        })
    }

})

/**
 * 
 * @param {String} text 
 * @returns Text avec (on espère) 0 mauvais inputs
 */
function cleanInputs(text)
{
    for(let i = 0; i < 100; i++)
    {
        text = text.replace("-", "");
        text = text.replace(";", "");
        text = text.replace("'", "");
        text = text.replace("\n", "");
        text = text.replace("\r", "");
    }
    return text;
}

function LogPropre(text)
{
    console.log(`[API] > ${text}`);
}