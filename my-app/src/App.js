import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import LoginPage from './pages/LoginPage'; 
import HomePage from './pages/HomePage';   
import AutomatPage from './pages/AutomatPage';
// Muut import-lauseet

function App() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginPage />} />
        <Route path="/automat" element={<AutomatPage />} />
        {/* Lisää reittejä tarvittaessa */}
      </Routes>
    </Router>
  );
}

export default App;