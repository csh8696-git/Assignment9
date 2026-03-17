# Assignment9

\## UE5 C++ Study Project - Based On Multi Game



\## Overview

This is a small unreal Engine 5.5 C++ study project focused on building a Multiplayer Number Baseball Game. the primary goal of this project is to understand the core principles of Server-Client architecture and Network Replication in UE5. Players compete to hues a hidden three-digit number while the server validates the logic and synchronizes the game state across all clients.





\## Implementation Process

//서버가 3자리 숫자를 생성 -> 올바른 순서의 사용자에게서 숫자입력받기-> 서버가 Win/S,B,O 판정 후 출력 전달

The server generates a 3-digit number -> Receiving number input from users in the correct order -> The server transmits output after determining Win/S, B, or O.

//PlayerState 가 주어진 기회 3회를 확인 및 숫자 입력 후 확인하는 메세지 출력

PlayerState checks the given 3 chances and displays a confirmation message after entering a number.

//승리, 무승부 후 게임 리셋 - 게임성을 위해 입력 후 승자/마지막 입력자가 추가 입력 시 리셋(추가 기능)

Game reset after win or draw - For gameplay, reset if the winner/last inputter makes an additional input after input (additional feature)

//생성, 입력에서 예외처리 필요(구현 단계에서 거의 다 되어있겠지만 재확인 및 커스텀 예외 추가)

Exception handling required for creation and input (although most of it is likely already done in the implementation phase, double-check and add custom exceptions)





\## Gameplay Structure

Server-Side Logic : The server generates a unique three-digit number at the start of the session and validates all player guesses to prevent cheating.

Turn-Based System : Implements a synchronized turn system to ensure players input their guesses in the correct order.

Result Calculation : The server calculates the "Strike" and "Ball" counts and broadcasts the result to all connected clients.

Exception Handling : Robust Validation for player inputs(e.g., checking for duplicate numbers, non-numeric characters, or out-of-bounds values).



\## Project Structure

GameModeBase : Manages the core game state, including the answer generation and win/loss conditions.

PlayerController : Handles player input and communicates with the server via RPCs.

GameState : Stores and replicates the current game progress and scoreboard to all players.

HUD/UserWidget : Provides a minimal UI for inputting numbers and displaying the match history.



\## Development Environment

Engine : Unreal Engine 5.5

Language : C++

IDE : Visual Studio 2022

Version Control : Git



