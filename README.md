📌 Final Year Development Project: PostureGuard – AI-Based Smart Sitting Posture Correction System
Overview: PostureGuard is an AI-integrated smart posture monitoring system designed to track a user’s sitting posture in real time and provide corrective guidance when poor posture is detected. By combining webcam-based posture recognition with a pressure-sensitive seat pad, the system accurately identifies slouching or leaning and delivers instant feedback.

## Key Features
### Dual-Source Posture Detection
Camera-Based Detection: Using Teachable Machine and Python (OpenCV), we trained a custom image classification model with real photos of various sitting postures (e.g., centered, leaning left/right, slouching). This model analyzes and recognizes the user’s posture in real time.
Pressure Sensor Pad: A custom Arduino-based pressure-sensitive seat pad programmed in C measures changes in weight distribution. It provides data on how and where the user is sitting to support accurate posture assessment.
Machine Learning Integration: Both visual data (from the camera) and pressure data (from the seat pad) are processed through machine learning models. By combining these two inputs, the system can more precisely classify the user’s sitting posture and provide a more refined analysis.
Real-Time Voice Feedback: When poor posture is detected, the system uses Text-to-Speech (TTS) technology to provide immediate voice alerts. For example, the system may say, “You are leaning to the right. Please sit upright,” encouraging instant correction.
Web Interface Visualization: A user-friendly HTML-based web dashboard visualizes both camera and pressure data in real time. Users can monitor their sitting posture through a browser and immediately see

## Technologies Used
Camera Module: Teachable Machine, Python, OpenCV
Seat Pad Module: Arduino, C
Web Interface: HTML, JavaScript
AI Models: Teachable Machine (image classification), Custom ML model for pressure data
Audio Feedback: Web Speech API / Python TTS

# Goal: The goal of PostureGuard is to promote healthy sitting habits and prevent posture-related health issues by offering an accessible,
