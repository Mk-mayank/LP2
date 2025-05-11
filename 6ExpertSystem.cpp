#include <iostream>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;

// BMI calculation
double bmiCalculator(double heightCM, double weightKG) {
    double heightM = heightCM / 100.0;
    double bmi = weightKG / (heightM * heightM);
    return round(bmi * 10.0) / 10.0;
}

void interpretBMI(double bmi) {
    cout << "BMI: " << bmi << " - ";
    if (bmi < 18.5) cout << "Underweight" << endl;
    else if (bmi <= 24.9) cout << "Normal (Good)" << endl;
    else if (bmi < 30) cout << "Overweight" << endl;
    else cout << "Obese" << endl;
}

// Diabetes evaluation
string calculateDiabetesRisk(double fasting, double postMeal, string history) {
    int score = 0;
    if (fasting >= 126) score += 2;
    if (postMeal >= 200) score += 2;
    if (history == "yes") score += 1;

    if (score >= 4) return "High";
    else if (score >= 2) return "Moderate";
    else return "Low";
}

bool evaluateDiabetes(double fasting, double postMeal, string history, unordered_map<string, string>& symptoms) {
    string risk = calculateDiabetesRisk(fasting, postMeal, history);
    cout << "\n🧪 Diabetes Risk Level: " << risk << endl;

    int symptomCount = 0;
    for (auto& s : symptoms)
        if (s.second == "yes") symptomCount++;

    if (fasting >= 126 || postMeal >= 200) {
        cout << "⚠️ Likely diabetic." << endl;
        if (history == "yes")
            cout << "Note: History present. Levels are critically high." << endl;
        else
            cout << "Warning: No prior history, but diabetic levels detected." << endl;
        cout << "📝 Suggestion: Consult a diabetologist.\n" << endl;
        return true;
    } else if ((100 <= fasting && fasting < 126) || (140 <= postMeal && postMeal < 200)) {
        cout << "⚠️ Pre-diabetic stage." << endl;
        cout << "📝 Suggestion: Monitor regularly, control diet.\n" << endl;
        return true;
    } else if (symptomCount > 0 && (fasting > 110 || postMeal > 160)) {
        cout << "⚠️ Elevated sugar + symptoms suggest early diabetes." << endl;
        cout << "📝 Suggestion: Get HbA1c test. See a physician.\n" << endl;
        return true;
    } else {
        cout << "✅ Sugar levels in safe range.\n" << endl;
        return false;
    }
}

// Hypertension evaluation
bool evaluateHypertension(int sys, int dia, unordered_map<string, string>& symptoms) {
    if (sys >= 140 || dia >= 90) {
        cout << "⚠️ Diagnosis: Hypertension (High BP)." << endl;
        if (symptoms["chest_pain"] == "yes")
            cout << "❗ Chest pain present. Emergency attention needed!" << endl;
        if (symptoms["headache"] == "yes")
            cout << "❗ Frequent headaches indicate vascular stress." << endl;
        cout << "📝 Suggestion: Monitor BP, reduce salt, consult cardiologist.\n" << endl;
        return true;
    } else if ((sys >= 120 && sys < 140) || (dia >= 80 && dia < 90)) {
        cout << "⚠️ Pre-hypertension stage." << endl;
        cout << "📝 Suggestion: Lifestyle change, monitor regularly.\n" << endl;
        return true;
    } else {
        cout << "✅ Blood pressure normal.\n" << endl;
        return false;
    }
}

// General symptom check
bool generalSymptomCheck(bool diabetesRisk, bool hypertensionRisk, unordered_map<string, string>& symptoms) {
    bool mildWarning = false;
    if (symptoms["frequent_thirst"] == "yes" || symptoms["frequent_urination"] == "yes" ||
        symptoms["blurred_vision"] == "yes" || symptoms["fatigue"] == "yes") {
        mildWarning = true;
        cout << "⚠️ Mild diabetes symptoms detected." << endl;
        cout << "📝 Suggestion: Repeat tests in 2 weeks.\n" << endl;
    } else if (!hypertensionRisk && 
               (symptoms["chest_pain"] == "yes" || symptoms["headache"] == "yes")) {
        mildWarning = true;
        cout << "⚠️ Headache/Chest pain without hypertension." << endl;
        cout << "📝 Suggestion: Could be stress-related. Consider ECG.\n" << endl;
    } else {
        cout << "✅ No mild symptoms. You're doing well!" << endl;
    }
    return mildWarning;
}

// Final summary
void finalSummary(int age, bool diabetesRisk, bool hypertensionRisk, bool mildWarning) {
    if (!diabetesRisk && !hypertensionRisk && !mildWarning) {
        cout << "\n✅ You are in good health based on provided inputs." << endl;
        if (age > 45)
            cout << "🔄 Tip: Regular checkups advised after 45.\n" << endl;
        else
            cout << "💪 Great! Keep maintaining a healthy lifestyle!\n" << endl;
    }
}

int main() {
    // Input
    int age, sysBP, diaBP;
    double height, weight, fasting, postMeal;
    string history;
    unordered_map<string, string> symptoms;

    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter height in cm: ";
    cin >> height;
    cout << "Enter weight in kg: ";
    cin >> weight;

    double bmi = bmiCalculator(height, weight);
    interpretBMI(bmi);

    cout << "\nEnter fasting blood sugar (mg/dL): ";
    cin >> fasting;
    cout << "Enter post-meal blood sugar (mg/dL): ";
    cin >> postMeal;
    cout << "History of diabetes? (yes/no): ";
    cin >> history;

    cout << "\nEnter systolic BP: ";
    cin >> sysBP;
    cout << "Enter diastolic BP: ";
    cin >> diaBP;

    // Symptom inputs
    cout << "\nDo you experience frequent thirst? (yes/no): ";
    cin >> symptoms["frequent_thirst"];
    cout << "Frequent urination? (yes/no): ";
    cin >> symptoms["frequent_urination"];
    cout << "Blurred vision? (yes/no): ";
    cin >> symptoms["blurred_vision"];
    cout << "Fatigue? (yes/no): ";
    cin >> symptoms["fatigue"];
    cout << "Chest pain? (yes/no): ";
    cin >> symptoms["chest_pain"];
    cout << "Headaches? (yes/no): ";
    cin >> symptoms["headache"];

    cout << "\n-------- HEALTH REPORT --------" << endl;

    bool diabetesRisk = evaluateDiabetes(fasting, postMeal, history, symptoms);
    bool hypertensionRisk = evaluateHypertension(sysBP, diaBP, symptoms);
    bool mildWarning = generalSymptomCheck(diabetesRisk, hypertensionRisk, symptoms);

    finalSummary(age, diabetesRisk, hypertensionRisk, mildWarning);
    return 0;
}
