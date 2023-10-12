from flask import Flask, render_template, request, jsonify
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')
    
@app.route('/home',methods=['POST'])	
def upload_file():
	uploaded_file = request.files['file']
	if uploaded_file.filename != '':
		upload_dir = 'Image'
		os.makedirs(upload_dir, exist_ok=True)
		file_address = os.path.join(upload_dir,uploaded_file.filename)
		uploaded_file.save(file_address)
		with open('file_address.txt','w') as file:
			file.write(file_address)
			return 'File uploaded successfully!'
	else:
		return 'No file selected'

@app.route('/execute', methods=['POST'])
def execute():
    action = request.form['action']
    output = ""

    if action == 'img_stat':
        # Compile and execute img_stat tool
        command = ['gcc', 'img_stat.c', '-o', 'img_stat']
        # Compile the C program if not already compiled
        subprocess.run(command)

        # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
        try:
            output = subprocess.check_output(['./img_stat'], stderr=subprocess.STDOUT, text=True)
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during img_stat execution.")

    if action == 'mmls':
        # Compile and execute mmls tool
        command = ['gcc', 'mmls.c', '-o', 'mmls']
        # Compile the C program if not already compiled
        subprocess.run(command)

        # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
        try:
            #output = subprocess.check_output(['./mmls', '/home/mahika/Downloads/CapstoneFramework/Mantooth_raw.dd.raw'], stderr=subprocess.STDOUT, text=True)
            output = subprocess.check_output(['./mmls'], stderr=subprocess.STDOUT, text=True)
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during mmls execution.")
            
    if action == 'fls':
        # Get the offset from the form data
        offset = request.form['offset']
        try:
            # Compile and execute fls tool
            command = ['gcc', 'fls.c', '-o', 'fls']
            subprocess.run(command)
            # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
            output = subprocess.check_output(['./fls', offset], stderr=subprocess.STDOUT, text=True)
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            #return e
            print(type(output))
            print(e)
            return jsonify(error="An error occurred during fls execution.")
            
    if action == 'fsstat':
        # Get the offset from the form data
        offset = request.form['offset']
  
        try:
            # Compile and execute fls tool
            command = ['gcc', 'fsstat.c', '-o', 'fsstat']
            subprocess.run(command)
            # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
            output = subprocess.check_output(['./fsstat', offset], stderr=subprocess.STDOUT, text=True)
            
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during fsstat execution.")
            
    if action == 'stringsearch':
        searchString = request.form['searchString']
        offset = request.form['offset']

        try:
            # Compile and execute stringsearch tool
            command = ['gcc', 'stringsearch.c', '-o', 'stringsearch']
            subprocess.run(command)

            # Execute the stringsearch program with offset and searchString as arguments
            output = subprocess.check_output(['./stringsearch', offset, searchString], stderr=subprocess.STDOUT, text=True)

            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during stringsearch execution.")
            
    if action == 'recover':
        dire = request.form['dire']
        offset = request.form['offset']
        print(offset)

        try:
            # Compile and execute recover tool
            command = ['gcc', 'tsk_recover.c', '-o', 'recover']
            subprocess.run(command)

            # Execute the tsk_recover program with offset and file name as arguments
            output = subprocess.check_output(['./recover', offset, dire], stderr=subprocess.STDOUT, text=True)

            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during recover execution.")
            
    if action == 'srch_strings':
        # Compile and execute srch_strings tool
        command = ['gcc', 'strings.c', '-o', 'string']
        # Compile the C program if not already compiled
        subprocess.run(command)

        # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
        try:
            output = subprocess.check_output(['./string'], stderr=subprocess.STDOUT, text=True)
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during srch_strings execution.")
           

    print(type(output))
    return output

if __name__ == '__main__':
    app.run(debug=True)
