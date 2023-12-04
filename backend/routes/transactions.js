const express = require('express');
const router = express.Router();
const transactionsmodel = require('../models/transactions_model');


router.get('/',
    function (request, response) {
        transactionsmodel.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/transfers_in/:to_account_id',
    function (request, response) {
        transactionsmodel.getTransfersInByAccountID(request.params.to_account_id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });

router.get('/transfers_out/:from_account_id',
    function (request, response) {
        transactionsmodel.getTransfersOutByAccountID(request.params.from_account_id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });

router.get('/all_transfers/:account_id', function (request, response) {
    transactionsmodel.getAllTransfersByAccountID(request.params.account_id, function (err, dbResult) {
        if (err) {
            response.status(500).json(err);
        } else {
            response.json(dbResult);
        }
    });
});

router.get('/last_five_transactions/:account_id', function (request, response) {
    transactionsmodel.getLastFiveTransactions(request.params.account_id, function (err, dbResult) {
        if (err) {
            response.status(500).json(err);
        } else {
            response.json(dbResult);
        }
    });
});

router.post('/transfer', function (req, res) {
    const { from_account_id, to_account_id, amount, description } = req.body;
    transactionsmodel.transferBalance(from_account_id, to_account_id, amount, description, function (err, result) {
        if (err) {
            res.status(500).json(err);
        } else {
            res.json(result);
        }
    });
});


router.post('/deposit', function (req, res) {
    const { account_id, amount } = req.body;
    transactionsmodel.deposit(account_id, amount, function (err, result) {
        if (err) {
            res.status(500).json(err);
        } else {
            res.json(result);
        }
    });
});

router.post('/withdraw', function (req, res) {
    const { account_id, amount } = req.body;
    transactionsmodel.withdraw(account_id, amount, function (err, result) {
        if (err) {
            res.status(500).json(err);
        } else {
            res.json(result);
        }
    });
});

module.exports = router;