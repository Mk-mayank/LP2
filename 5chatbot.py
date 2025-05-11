import gradio as gr
import random
from nltk.corpus import wordnet
from nltk.stem import WordNetLemmatizer
from nltk.tokenize import word_tokenize
from nltk import pos_tag

# NLP Setup
lemmatizer = WordNetLemmatizer()

def get_wordnet_pos(treebank_tag):
    if treebank_tag.startswith('J'):
        return wordnet.ADJ
    elif treebank_tag.startswith('V'):
        return wordnet.VERB
    elif treebank_tag.startswith('N'):
        return wordnet.NOUN
    elif treebank_tag.startswith('R'):
        return wordnet.ADV
    else:
        return wordnet.NOUN

def preprocess_text(text):
    text = text.lower()
    tokens = word_tokenize(text)
    tagged_tokens = pos_tag(tokens)
    return [lemmatizer.lemmatize(word=word, pos=get_wordnet_pos(tag)) for word, tag in tagged_tokens]

# Rules

rules = {
    # --- Basic Greetings & Farewells ---
    ('hello', 'hi', 'hey', 'greeting', 'wassup'):
        ["Hello there! Welcome to our cafe. How can I help you today?", "Hi! What can I get for you?", "Hey! Good to see you."],
    ('thank', 'thanks', 'appreciate'):
        ["You're welcome!", "No problem! Enjoy your time here.", "Happy to help!"],
    ('bye', 'goodbye', 'exit', 'quit', 'see you'):
        ["Goodbye! Hope to see you again soon.", "Farewell! Have a wonderful day.", "Bye! Come back anytime."],

    # --- Cafe Specific ---
    ('menu', 'offer', 'serve', 'selection', 'list'):
        ["You can find our full menu on the board above the counter.", "Our menu includes various coffees, teas, pastries, sandwiches, and snacks."],
    ('coffee', 'brew', 'drip', 'filter', 'cup'):
        ["We have a variety of freshly brewed coffees! Anything specific you'd like?", "Our coffee selection includes drip, pour-over, and espresso-based drinks. Check the menu!", "Yes, we serve delicious coffee. Our baristas can help you choose."],
    ('latte', 'cappuccino', 'espresso', 'americano', 'mocha', 'macchiato', 'flat white'): 
        ["Yes, we make those! Check our menu board for details and options like milk choices.", "Absolutely, that's on our menu.", "We can definitely make that for you."],
    ('tea', 'chai'):
        ["We have a selection of teas, including black, green, herbal infusions, and chai latte.", "Yes, we offer various types of tea. What kind are you in the mood for?", "Tea is available. Please ask the barista about today's selection or see the menu."],
    ('food', 'eat', 'hungry', 'snack', 'pastry', 'cake', 'muffin', 'croissant', 'sandwich', 'bite'):
        ["We have a delicious selection of pastries, sandwiches, cakes, and snacks. Check our display case or menu board!", "Feeling hungry? We offer freshly baked goods and light meals.", "Yes, we have food options available. See our menu or ask our staff."],
    ('wifi', 'internet', 'wi-fi', 'network', 'password'):
        ["Yes, we offer free WiFi for customers. The network name is 'CafeConnect_Guest' and the password is 'enjoyyourcoffee'.", "Free WiFi is available! The password should be on a sign near the counter, or just ask.", "Yes, WiFi is available for our guests. Network: CafeConnect_Guest, Password: enjoyyourcoffee"],
    ('pay', 'payment', 'card', 'cash', 'credit', 'upi', 'gpay', 'paytm', 'phonepe', 'scan'): 
        ["We accept cash, credit/debit cards, and major UPI payments (like GPay, PhonePe, Paytm).", "You can pay with cash, card, or UPI scan.", "Payment options include cash, all major cards, and UPI apps."],
    ('special', 'deal', 'offer', 'discount', 'promotion', 'combo'):
        ["Ask our barista about today's specials or any ongoing combos!", "We sometimes have seasonal offers. Please check the board or ask our staff.", "Check our board near the counter for any current deals or special offers."],
    ('vegan', 'vegetarian', 'gluten-free', 'allergy', 'dairy-free', 'milk', 'soy', 'oat', 'almond'): 
        ["We offer vegetarian options and alternative milks (like oat or almond). Please mention any allergies or dietary needs when ordering.", "We have options! Let the barista know your requirements when you order.", "Please inform our staff about any allergies. We have oat and almond milk available."],
    ('restroom', 'bathroom', 'toilet', 'washroom', 'loo'):
        ["The restroom is located at the back, just past the counter to the left.", "Yes, the washroom is available for customers. It's down that short hallway.", "The restroom is just around the corner there."],
    ('book', 'reservation', 'reserve', 'table'):
        ["We generally operate on a first-come, first-served basis, but you can call ahead for larger groups.", "Reservations aren't usually required, just come on in!", "We don't typically take reservations, but feel free to walk in!"],
    ('music', 'song', 'playlist', 'volume'):
        ["We play a curated playlist. Hope you enjoy the vibes!", "Glad you noticed the music! It's a mix we enjoy.", "If the music volume is uncomfortable, please let our staff know."],

    # --- General Info ---
    ('hour', 'open', 'close', 'time', 'timing'):
        ["Our cafe hours are 8 AM to 8 PM, seven days a week.", "We're open from 8 in the morning until 8 in the evening daily.", "Opening hours: 8:00 AM - 8:00 PM everyday."],
    ('location', 'address', 'where', 'find'):
        ["We're located at 15 Cafe Lane, Koregaon Park, Pune.", "You can find us at 15 Cafe Lane in KP.", "Our address is 15 Cafe Lane, Pune. Easy to find!"], # Example Pune Address
    ('help', 'assist', 'support', 'question'):
        ["Sure, I can try to help. What's your question about our cafe?", "How can I assist you regarding the cafe?", "I can answer questions about our menu, hours, WiFi, etc. What would you like to know?"]
}

# Response Generator

def get_response(user_input):
    lemmas = preprocess_text(user_input)
    for keywords, responses in rules.items():
        for keyword in keywords:
            if keyword in lemmas:
                return random.choice(responses)
    return "I'm sorry, I didn't quite get that."

           

# Gradio Interface
def chatbot(input_text):
    return get_response(input_text)

# Launch Gradio Interface
iface = gr.Interface(fn=chatbot, 
                     inputs="text", 
                     outputs="text", 
                     title="Cafe Chatbot", 
                     description="Ask me anything about our cafe! (e.g., menu, hours, coffee, etc.)")
iface.launch()
