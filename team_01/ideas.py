import random

def generate_idea_brainstorm(topic):
    taglines = [
        "Think Big. Start Small.",
        "Make It Matter.",
        "Less Noise. More Impact.",
        "Because Ideas Deserve Action."
    ]
    analogies = [
        f"{topic.capitalize()} is like trying to fill a leaking bucket.",
        f"Solving {topic} is like solving a puzzle with no edges.",
        f"{topic.capitalize()} is the elephant in the room we pretend not to see."
    ]
    questions = [
        f"What if we could solve {topic} with AI?",
        f"What would {topic} look like in 2050?",
        f"Who benefits most from solving {topic} — and who loses?",
        f"What if kids designed the solution for {topic}?"
    ]
    ideas = [
        f"An app that turns {topic} into community action.",
        f"A sensor that detects {topic}-related patterns and alerts users.",
        f"A game that educates people about {topic}.",
        f"A toolkit for schools to explore {topic} with students."
    ]
    return {
        "topic": topic,
        "ideas": random.sample(ideas, 2),
        "taglines": random.sample(taglines, 2),
        "analogies": random.sample(analogies, 2),
        "questions": random.sample(questions, 2)
    }
