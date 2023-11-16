const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/cards_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.card_id && request.body.pin_hashed){
      const user = request.body.card_id;
      const pass = request.body.pin_hashed;
      
        login.checkPassword(user, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pass,dbResult[0].pin_hashed, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ card_id: user });
                  response.send(token);
                }
                else {
                    console.log("wrong pin");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("card_id or pin missing");
      response.send(false);
    }
  }
);

function generateAccessToken(card_id) {
  dotenv.config();
  return jwt.sign(card_id, process.env.Tokeni, { expiresIn: '1800s' });
}

module.exports=router;