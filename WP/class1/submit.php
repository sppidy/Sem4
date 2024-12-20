<?php
// Check if the form was submitted using the POST method
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Sanitize and validate form inputs
    $fname = htmlspecialchars(trim($_POST['fname']));
    $lname = htmlspecialchars(trim($_POST['lname']));
    $email = filter_var(trim($_POST['mail']), FILTER_SANITIZE_EMAIL);
    $phone = htmlspecialchars(trim($_POST['phno']));
    $dob = htmlspecialchars(trim($_POST['dob']));
    $address = htmlspecialchars(trim($_POST['address']));
    $gender = htmlspecialchars(trim($_POST['gender']));
    $hobbies = isset($_POST['hobbies']) ? $_POST['hobbies'] : [];
    $browser = htmlspecialchars(trim($_POST['browsers']));

    // Validate email
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        die("Invalid email format.");
    }

    // Validate phone number (should be 10 digits`)
    if (!preg_match("/^[0-9]{10}$/", $phone)) {
        die("Invalid phone number. It should be exactly 10 digits.");
    }

    // Display the submitted information
    echo "<h1>Form Submission Successful!</h1>";
    echo "<h2>Your Submitted Information:</h2>";
    echo "<p><strong>First Name:</strong> $fname</p>";
    echo "<p><strong>Last Name:</strong> $lname</p>";
    echo "<p><strong>Email:</strong> $email</p>";
    echo "<p><strong>Phone:</strong> $phone</p>";
    echo "<p><strong>Date of Birth:</strong> $dob</p>";
    echo "<p><strong>Address:</strong> $address</p>";
    echo "<p><strong>Gender:</strong> $gender</p>";

    echo "<p><strong>Hobbies:</strong><br>";
    if (!empty($hobbies)) {
        foreach ($hobbies as $hobby) {
            echo "- $hobby<br>";
        }
    } else {
        echo "No hobbies selected.<br>";
    }
    echo "</p>";

    echo "<p><strong>Favorite Browser:</strong> $browser</p>";

    // Optionally, save data to a database, send an email, or log it for later processing
    // Example: save the data to a database (requires database connection code)
} else {
    // If the form was not submitted using POST, display an error or redirect
    echo "Please submit the form.";
}
?>
