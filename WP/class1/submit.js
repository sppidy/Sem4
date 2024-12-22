document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('myForm');

    form.addEventListener('submit', function(event) {
        event.preventDefault(); // Prevent form from submitting the traditional way

        // Sanitize and validate form inputs
        const fname = form.fname.value.trim();
        const lname = form.lname.value.trim();
        const email = form.mail.value.trim();
        const phone = form.phno.value.trim();
        const dob = form.dob.value.trim();
        const address = form.address.value.trim();
        const gender = form.gender.value.trim();
        const hobbies = Array.from(form.hobbies).filter(hobby => hobby.checked).map(hobby => hobby.value);
        const browser = form.browsers.value.trim();

        // Validate email
        if (!/^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$/.test(email)) {
            alert('Invalid email format.');
            return;
        }

        // Validate phone number (should be 10 digits)
        if (!/^[0-9]{10}$/.test(phone)) {
            alert('Invalid phone number. It should be exactly 10 digits.');
            return;
        }

        // Display the submitted information
        const resultDiv = document.getElementById('result');
        resultDiv.innerHTML = `
            <h1>Form Submission Successful!</h1>
            <h2>Your Submitted Information:</h2>
            <p><strong>First Name:</strong> ${fname}</p>
            <p><strong>Last Name:</strong> ${lname}</p>
            <p><strong>Email:</strong> ${email}</p>
            <p><strong>Phone:</strong> ${phone}</p>
            <p><strong>Date of Birth:</strong> ${dob}</p>
            <p><strong>Address:</strong> ${address}</p>
            <p><strong>Gender:</strong> ${gender}</p>
            <p><strong>Hobbies:</strong><br>${hobbies.length > 0 ? hobbies.join('<br>') : 'No hobbies selected.'}</p>
            <p><strong>Favorite Browser:</strong> ${browser}</p>
        `;
    });
});