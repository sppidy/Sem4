document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('as1form');

    form.addEventListener('submit', function(event) {
        event.preventDefault();

        const pname = form.pname.value.trim();
        const ppls = form.ppls.value.trim();
        const psdate = form.psdate.value.trim();
        const pedate = form.pedate.value.trim();
        const ppriority = form.ppriority.value;
        const pdesc = form.pdesc.value.trim();

        if (!pname || !ppls || !psdate || !pedate || !ppriority || !pdesc) {
            alert('Please fill out all required fields.');
            return;
        }

        const resultDiv = document.createElement('div');
        resultDiv.innerHTML = `
            <h1>Form Submission Successful!</h1>
            <h2>Your Submitted Information:</h2>
            <p><strong>Project Name:</strong> ${pname}</p>
            <p><strong>Assigned to:</strong> ${ppls}</p>
            <p><strong>Start Date:</strong> ${psdate}</p>
            <p><strong>End Date:</strong> ${pedate}</p>
            <p><strong>Priority:</strong> ${ppriority}</p>
            <p><strong>Description:</strong> ${pdesc}</p>
        `;

        document.body.appendChild(resultDiv);

        form.reset();
    });
});