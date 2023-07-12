from flask import Flask, render_template, request
import qrcode
from io import BytesIO
import base64

# Configure application
app = Flask(__name__)


@app.route("/", methods=['POST', 'GET'])
def index():
    return render_template("index.html")

@app.route("/generate", methods=["POST", "GET"])
def generate():
    if request.method == 'POST':

        color_id = request.form.get("qr_color")
        background_color = request.form.get("bg_color")
        url = request.form.get("qr_link")
        checkbox_value = request.form.get('transparent')

        qr = qrcode.QRCode(
            version=2,
            error_correction=qrcode.constants.ERROR_CORRECT_L,
            box_size=10,
            border=4
        )

        qr.add_data(url)
        qr.make(fit=True)

        if checkbox_value:
            imagem = qr.make_image(fill_color=color_id, back_color='transparent')
        else:
            imagem = qr.make_image(fill_color=color_id, back_color=background_color)

        if color_id == '#ffffff':
            bg_col2 = 'bg-black'
        else:
            bg_col2 = None


        img_buffer_png = BytesIO()
        imagem.save(img_buffer_png, format='PNG')
        img_buffer_png.seek(0)

        # Encode the image as a Base64 string
        img_str_png = base64.b64encode(img_buffer_png.read()).decode('utf-8')


        return render_template("generate.html", qr=img_str_png, bg_col2=bg_col2)
    return render_template("generate.html")
