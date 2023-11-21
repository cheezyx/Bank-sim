import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import LoginPage from './pages/LoginPage'; // Jos LoginPage.js on pages-kansiossa
import HomePage from './pages/HomePage';   // Jos HomePage.js on pages-kansiossa
// Muut import-lauseet

function App() {
  return (
    <Router>
      <Routes>
        <Route path="/login" element={<LoginPage />} />
        <Route path="/" element={<HomePage />} />
        {/* Lisää reittejä tarvittaessa */}
      </Routes>
    </Router>
  );
}

export default App;