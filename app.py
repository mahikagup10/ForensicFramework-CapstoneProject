from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

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
     
    if action == 'icat':
        # Get the offset from the form data
        offset = request.form['offset']
        inode = request.form['inode']
  
        try:
            # Compile and execute fls tool
            command = ['gcc', 'icat.c', '-o', 'icat']
            subprocess.run(command)
            # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
            output = subprocess.check_output(['./icat', offset, inode], stderr=subprocess.STDOUT, text=True)
            
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during icat execution.")
            

    if action == 'istat':
        # Get the offset from the form data
        offset = request.form['offset']
        inode = request.form['inode']
  
        try:
            # Compile and execute fls tool
            command = ['gcc', 'istat.c', '-o', 'istat']
            subprocess.run(command)
            # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
            output = subprocess.check_output(['./istat', offset, inode], stderr=subprocess.STDOUT, text=True)
            
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            return jsonify(error="An error occurred during istat execution.")

    if action == 'sorter':
        # Get the offset from the form data
        offset = request.form['offset']
        try:
            # Compile and execute fls tool
            command = ['gcc', 'sorter.c', '-o', 'sorter']
            subprocess.run(command)
            # Replace '/path/to/your/image.dd' with the actual path to your forensic image file
            output = subprocess.check_output(['./sorter', offset], stderr=subprocess.STDOUT, text=True)
            # Wrap the output in <pre> tags and replace newlines with <br> tags
            output = '<pre>' + output.replace('\n', '<br>') + '</pre>'
        except subprocess.CalledProcessError as e:
            # Handle errors here, for example:
            #return e
            print(type(output))
            print(e)
            return jsonify(error="An error occurred during fls execution.")

    
    return output

if __name__ == '__main__':
    app.run(debug=True)
