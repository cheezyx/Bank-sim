import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';

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
        setShowTransactionForm(false); // Sulje lomake
        setTransactionAmount('');
        setTransactionDescription('');
        fetchAccountDetails(); 
    } catch (error) {
        console.error('Transaction error:', error);
    }
};

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

return (
    <div>
        {name ? <h1>Hei {name}!</h1> : <p>Ladataan...</p>}
        <button onClick={handleShowAccountDetails}>
            {showAccountDetails ? 'Piilota saldo' : 'Näytä saldo'}
        </button>
        {showAccountDetails && (
            <div>
                <h2>Tilitiedot</h2>
                {selectedAccount ? (
                    <div>
                        <p>Tilin tyyppi: {selectedAccount.account_type}</p>
                        <p>Saldo: {selectedAccount.balance}</p>
                        {selectedAccount.credit_limit && <p>Limiitti: {selectedAccount.credit_limit}</p>}
                    </div>
                ) : (
                    accounts.map((account, index) => (
                        <div key={index}>
                            <p>Tilin tyyppi: {account.account_type}</p>
                            <p>Saldo: {account.balance}</p>
                            {account.credit_limit && <p>Limiitti: {account.credit_limit}</p>}
                        </div>
                    ))
                )}
            </div>
        )}
        <button onClick={() => {
            setTransactionType('withdraw');
            setShowTransactionForm(true);
        }}>Nosto</button>
        <button onClick={() => {
            setTransactionType('deposit');
            setShowTransactionForm(true);
        }}>Talletus</button>

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
        <button disabled>Siirto</button>
        <button onClick={handleLogout}>Kirjaudu ulos</button>
    </div>
);
}

export default AutomatPage;