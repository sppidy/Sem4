document.addEventListener("DOMContentLoaded", function () {
    const form = document.getElementById("as1form");

    form.addEventListener("submit", function (e) {
        const name = document.getElementById("name").value.trim();
        if (!/^[a-zA-Z\s]+$/.test(name)) {
            alert("Please enter a valid name (letters and spaces only).");
            e.preventDefault();
            return;
        }

        const email = document.getElementById("email").value.trim();
        if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
            alert("Please enter a valid email address.");
            e.preventDefault();
            return;
        }

        const phone = document.getElementById("phone").value.trim();
        if (!/^\+\d{10,15}$/.test(phone)) {
            alert("Please enter a valid phone number (e.g., +4450000000000).");
            e.preventDefault();
            return;
        }

        const postcode = document.getElementById("postcode").value.trim();
        if (!/^[A-Za-z0-9\s]+$/.test(postcode)) {
            alert("Please enter a valid postcode.");
            e.preventDefault();
            return;
        }

        const cardNumber = document.getElementById("cardnumber").value.trim();
        if (!/^\d{16}$/.test(cardNumber)) {
            alert("Please enter a valid 16-digit card number.");
            e.preventDefault();
            return;
        }

        const scode = document.getElementById("scode").value.trim();
        if (!/^\d{3,4}$/.test(scode)) {
            alert("Please enter a valid security code (3 or 4 digits).");
            e.preventDefault();
            return;
        }

        const cname = document.getElementById("cname").value.trim();
        if (!/^[a-zA-Z\s]+$/.test(cname)) {
            alert("Please enter the name as it appears on the card.");
            e.preventDefault();
            return;
        }
    });
});
