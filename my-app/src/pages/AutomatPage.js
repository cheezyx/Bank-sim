import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import './AutomatPage.css';

function AutomatPage() {
    const [name, setName] = useState('');
    const [accounts, setAccounts] = useState([]);
    const [selectedAccount, setSelectedAccount] = useState(null);
    const [showAccountDetails, setShowAccountDetails] = useState(false);
    const [showTransactionForm, setShowTransactionForm] = useState(false);
    const [transactionType, setTransactionType] = useState('');
    const [transactionAmount, setTransactionAmount] = useState('');
    const [transactionDescription, setTransactionDescription] = useState('');
    const cardId = localStorage.getItem('card_id');
    const selectedCardType = localStorage.getItem('selected_card_type');
    const token = localStorage.getItem('token');
    const navigate = useNavigate();
    const [message, setMessage] = useState('');
    const [transactions, setTransactions] = useState([]);
    const [showTransactions, setShowTransactions] = useState(false);
    const [toAccountId, setToAccountId] = useState('');
    const [showTransferForm, setShowTransferForm] = useState(false);
    const [isTransactionActive, setIsTransactionActive] = useState(false);



    const openTransactionForm = (type) => {
        setTransactionType(type);
        setShowTransactionForm(true);
        setIsTransactionActive(true);
    };

    const closeTransactionForm = () => {
        setShowTransactionForm(false);
        setIsTransactionActive(false);
    };

    const handleTransfer = async () => {
        const url = `http://localhost:3000/transactions/transfer`;

        const body = {
            from_account_id: selectedAccount.account_id,
            to_account_id: toAccountId,
            amount: transactionAmount,
            description: transactionDescription
        };

        try {
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`
                },
                body: JSON.stringify(body)
            });
            const result = await response.json();
            console.log(result);
            setMessage(result.message); // Tallenna viesti tilamuuttujaan
            setShowTransferForm(false); // Sulje lomake
            setTransactionAmount('');
            setTransactionDescription('');
            setToAccountId('');
            fetchAccountDetails();
        } catch (error) {
            console.error('Transfer error:', error);
        }
    };

    const fetchTransactions = () => {
        if (selectedAccount) {
            fetch(`http://localhost:3000/transactions/all_transfers/${selectedAccount.account_id}`, {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            })
                .then(response => response.json())
                .then(data => {
                    // Kääntää saadun datan järjestyksen ja ottaa viisi viimeisintä alkiota
                    const latestTransactions = data.slice().reverse().slice(0, 5);
                    setTransactions(latestTransactions); // Tallentaa viisi viimeisintä tilitapahtumaa
                })
                .catch(error => console.error('Error:', error));
        }
    };


    const fetchAccountDetails = () => {
        fetch(`http://localhost:3000/cards/accountinf/${cardId}`, {
            headers: {
                'Authorization': `Bearer ${token}`
            }
        })
            .then(response => response.json())
            .then(data => {
                setAccounts(data);
                if (selectedCardType) {
                    const account = data.find(account => account.account_type === selectedCardType);
                    setSelectedAccount(account);
                } else if (data.length === 1) {
                    setSelectedAccount(data[0]);
                }
            })
            .catch(error => console.error('Error:', error));
    };

    const handleTransaction = async () => {
        const url = `http://localhost:3000/transactions/${transactionType}`;

        const body = {
            account_id: selectedAccount.account_id,
            amount: transactionAmount,
            description: transactionDescription
        };

        try {
            const response = await fetch(url, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`
                },
                body: JSON.stringify(body)
            });
            const result = await response.json();
            console.log(result);
            setMessage(result.message); // Tallenna viesti tilamuuttujaan
            setShowTransactionForm(false); // Sulje lomake
            setTransactionAmount('');
            setTransactionDescription('');
            fetchAccountDetails();
        } catch (error) {
            console.error('Transaction error:', error);
        }
    };

    const handleShowTransactions = () => {
        setShowTransactions(!showTransactions);
        fetchTransactions();
    };

    useEffect(() => {
        if (message) {
            const timer = setTimeout(() => {
                setMessage('');
            }, 5000); // Tyhjentää viestin 5 sekunnin kuluttua

            return () => clearTimeout(timer); // Siivousfunktio
        }
    }, [message]);

    useEffect(() => {
        if (cardId && token) {
            // Hae käyttäjän nimi
            fetch(`http://localhost:3000/cards/owner/${cardId}`, {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            })
                .then(response => response.json())
                .then(data => {
                    if (data && data.length > 0) {
                        const ownerName = `${data[0].first_name} ${data[0].last_name}`;
                        setName(ownerName);
                    }
                })
                .catch(error => console.error('Error:', error));

            // Hae tilitiedot
            fetch(`http://localhost:3000/cards/accountinf/${cardId}`, {
                headers: {
                    'Authorization': `Bearer ${token}`
                }
            })
                .then(response => response.json())
                .then(data => {
                    setAccounts(data);
                    if (selectedCardType) {
                        const account = data.find(account => account.account_type === selectedCardType);
                        setSelectedAccount(account);
                    } else if (data.length === 1) {
                        setSelectedAccount(data[0]);
                    }
                })
                .catch(error => console.error('Error:', error));
        }
        fetchAccountDetails();
    }, [cardId, token, selectedCardType]);

    const handleShowAccountDetails = () => {
        setShowAccountDetails(!showAccountDetails);
        fetchAccountDetails();
    };

    const handleLogout = () => {
        localStorage.clear();
        navigate('/');
    };

    function formatDate(dateString) {
        const options = { year: 'numeric', month: '2-digit', day: '2-digit', hour: '2-digit', minute: '2-digit' };
        return new Date(dateString).toLocaleDateString('fi-FI', options).replace(/\//g, '.');
    }

    return (
        <div className="automat-container">
            <div className="automat-box">
                {name ? <h1>Hei {name}!</h1> : <p>Ladataan...</p>}

                {!showTransactionForm && !showTransferForm && (
                    <>
                        <button onClick={handleShowAccountDetails}>
                            {showAccountDetails ? 'Piilota saldo' : 'Saldo'}
                        </button>
                        <button onClick={() => {
                            setTransactionType('withdraw');
                            setShowTransactionForm(true);
                        }}>Nosto</button>
                        <button onClick={() => {
                            setTransactionType('deposit');
                            setShowTransactionForm(true);
                        }}>Talletus</button>
                        <button onClick={() => {
                            setTransactionType('transfer');
                            setShowTransferForm(true);
                        }}>Siirto</button>
                        <button onClick={handleShowTransactions}>
                            {showTransactions ? 'Piilota tilitapahtumat' : 'Tilitapahtumat'}
                        </button>
                    </>
                )}

                {showAccountDetails && (
                    <div>
                        <h2>Tilitiedot</h2>
                        {selectedAccount ? (
                            <div style={{
                                padding: '10px',
                                margin: '5px 0',
                                backgroundColor: '#e0e0e0',
                            }}>
                                <p><strong>Tilinumero:</strong> {selectedAccount.account_id}</p>
                                <p><strong>Tyyppi:</strong> {selectedAccount.account_type}</p>
                                <p><strong>Saldo:</strong> {selectedAccount.balance}</p>
                                {selectedAccount.account_type === 'credit' && selectedAccount.credit_limit && (
                                    <p><strong>Luottoraja:</strong> {selectedAccount.credit_limit}</p>
                                )}
                            </div>
                        ) : (
                            accounts.map((account, index) => (
                                <div key={index} style={{
                                    padding: '10px',
                                    margin: '5px 0',
                                    backgroundColor: index % 2 === 0 ? '#e0e0e0' : '#ffffff',
                                }}>
                                    <p><strong>Tilin tyyppi:</strong> {account.account_type}</p>
                                    <p><strong>Saldo:</strong> {account.balance}</p>
                                    {account.account_type === 'credit' && account.credit_limit && (
                                        <p><strong>Luottoraja:</strong> {account.credit_limit}</p>
                                    )}
                                </div>
                            ))
                        )}
                    </div>
                )}

                {showTransactionForm && (
                    <div>
                        <h3>{transactionType === 'deposit' ? 'Talletus' : 'Nosto'}</h3>
                        <input
                            type="number"
                            value={transactionAmount}
                            onChange={(e) => setTransactionAmount(e.target.value)}
                            placeholder="Määrä"
                        />
                        <input
                            type="text"
                            value={transactionDescription}
                            onChange={(e) => setTransactionDescription(e.target.value)}
                            placeholder="Kuvaus"
                        />
                        <button onClick={handleTransaction}>Vahvista</button>
                        <button onClick={() => setShowTransactionForm(false)}>Peruuta</button>
                    </div>
                )}

                {showTransferForm && (
                    <div>
                        <h3>Siirto</h3>
                        <input
                            type="number"
                            value={toAccountId}
                            onChange={(e) => setToAccountId(e.target.value)}
                            placeholder="Vastaanottajan tilinumero"
                        />
                        <input
                            type="number"
                            value={transactionAmount}
                            onChange={(e) => setTransactionAmount(e.target.value)}
                            placeholder="Määrä"
                        />
                        <input
                            type="text"
                            value={transactionDescription}
                            onChange={(e) => setTransactionDescription(e.target.value)}
                            placeholder="Kuvaus"
                        />
                        <button onClick={handleTransfer}>Vahvista</button>
                        <button onClick={() => setShowTransferForm(false)}>Peruuta</button>
                    </div>
                )}

                {showTransactions && (
                    <div>
                        <h2>Tilitapahtumat</h2>
                        {transactions.map((transaction, index) => (
                            <div key={index} className="transaction-detail">
                                <p><strong>Tilitapahtuma:</strong> {transaction.transaction_type}</p>
                                <p><strong>Määrä:</strong> {transaction.amount}</p>
                                <p><strong>Kuvaus:</strong> {transaction.description}</p>
                                <p><strong>Aika:</strong> {formatDate(transaction.date_time)}</p>
                            </div>
                        ))}
                    </div>
                )}

                <button onClick={handleLogout} className="logout-button">Kirjaudu ulos</button>
                {message && <div className="message-box">{message}</div>}
            </div>
        </div>
    );
}

export default AutomatPage;