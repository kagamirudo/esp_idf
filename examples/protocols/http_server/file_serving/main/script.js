function setpath() {
    const fileInput = document.getElementById("newfile").files[0];
    if (fileInput) {
        document.getElementById("filepath").value = fileInput.name;
    }
}

function upload() {
    const filePath = document.getElementById("filepath").value.trim();
    const fileInput = document.getElementById("newfile").files;
    const uploadPath = "/upload/" + filePath;
    const MAX_FILE_SIZE = 200 * 1024; // 200KB

    if (fileInput.length === 0) {
        alert("Please select a file to upload.");
        return;
    }
    if (filePath === "") {
        alert("Please specify the file path on the server.");
        return;
    }
    if (filePath.includes(" ")) {
        alert("The file path cannot contain spaces.");
        return;
    }
    if (filePath.endsWith("/")) {
        alert("Please specify a file name in the path.");
        return;
    }
    if (fileInput[0].size > MAX_FILE_SIZE) {
        alert(`File size must be less than ${MAX_FILE_SIZE / 1024}KB.`);
        return;
    }

    disableInputs(true);

    const file = fileInput[0];
    const xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (xhttp.readyState === XMLHttpRequest.DONE) {
            if (xhttp.status === 200) {
                document.open();
                document.write(xhttp.responseText);
                document.close();
            } else {
                handleError(xhttp.status, xhttp.responseText);
            }
            disableInputs(false);
        }
    };

    xhttp.open("POST", uploadPath, true);
    xhttp.send(file);
}

function disableInputs(disable) {
    document.getElementById("newfile").disabled = disable;
    document.getElementById("filepath").disabled = disable;
    document.getElementById("upload").disabled = disable;
}

function handleError(status, responseText) {
    const errorMessages = {
        0: "Server closed the connection abruptly!",
        400: "Bad Request: Check the file and path.",
        413: "File Too Large: Ensure the file is under the size limit.",
        500: "Server Error: Try again later.",
    };

    const message = errorMessages[status] || `${status} Error: ${responseText}`;
    alert(message);
    location.reload();
}