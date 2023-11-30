import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import './LoginPage.css';

function LoginPage() {
  const [cardId, setCardId] = useState('');
  const [pin, setPin] = useState('');
  const [message, setMessage] = useState('');
  const [isLoading, setIsLoading] = useState(false);
  const navigate = useNavigate();

  const handleSubmit = async (event) => {
    event.preventDefault();
    setIsLoading(true);
    try {
      const loginResponse = await fetch('http://localhost:3000/login', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ card_id: cardId, pin_hashed: pin }),
      });

      if (loginResponse.ok) {
        const token = await loginResponse.text();
        if (token && token !== 'false') {
          localStorage.setItem('token', token);
          localStorage.setItem('card_id', cardId);

          // Hae kortin tiedot
          const cardResponse = await fetch(`http://localhost:3000/cards/${cardId}`, {
            headers: {
              'Authorization': `Bearer ${token}`
            }
          });

          if (cardResponse.ok) {
            const cardDataArray = await cardResponse.json();
            if (cardDataArray.length > 0 && cardDataArray[0].card_type.toLowerCase() === 'dual') {
              // Hae korttiin liittyvät tilit ennen kuin ohjaat eteenpäin
              const accountsResponse = await fetch(`http://localhost:3000/cards/accountinf/${cardId}`, {
                headers: {
                  'Authorization': `Bearer ${token}`
                }
              });
              if (accountsResponse.ok) {
                const accountsData = await accountsResponse.json();
                // Tallenna tilitiedot, esimerkiksi local storageen tai contextiin
                localStorage.setItem('accounts', JSON.stringify(accountsData));
              } else {
                // Käsittele virhetilanne
                console.error('Error fetching accounts data');
              }
              navigate('/cardTypeSelection');
            } else {
              navigate('/automat');
            }
          } else {
            setMessage('Error fetching card data');
          }
        } else {
          setMessage('Password incorrect or user does not exist');
        }
      } else {
        setMessage('An error occurred');
      }
    } catch (error) {
      console.error('Kirjautumisessa tapahtui virhe:', error);
      setMessage('An error occurred during login');
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div className="login-container">
      <div className="login-box">
        <h1>Kirjaudu sisään</h1>
        <form onSubmit={handleSubmit}>
          <label>
            Kortin ID:
            <input 
              type="text" 
              value={cardId} 
              onChange={(e) => setCardId(e.target.value)} 
              required 
            />
          </label>
          <label>
            PIN-koodi:
            <input 
              type="password" 
              value={pin} 
              onChange={(e) => setPin(e.target.value)} 
              required 
            />
          </label>
          <button type="submit" disabled={isLoading}>
            {isLoading ? 'Loading...' : 'Kirjaudu'}
          </button>
        </form>
        {message && <p>{message}</p>}
      </div>
    </div>
  );
}

export default LoginPage;

