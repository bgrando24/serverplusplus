# Server++

A modular, extensible, and scalable web server application framework written in C++.

The Server++ framework provides important core features such as HTTP request/response handling, native JSON support, and HTTPS implementation. However, the power of Server++ comes from its more advanced built-in features such as caching, load balancing, multithreading, authentication/authorisation, and more!

# Table of Contents

1. [Getting Started](#getting-started)
2. [About Server++](#about-server++)
3. [Features](#features)
   - [Core Services Engine](#core-services-engine)
   - [Cryptography Engine](#cryptography-engine)
   - [Logging Engine](#logging-engine)
   - [Caching Engine](#caching-engine)
   - [Load Balancing Engine](#load-balancing-engine)
   - [Storage Engine](#storage-engine)
   - [Proxy Engine](#proxy-engine)
   - [Security Engine](#security-engine)
   - [Communication Protocol Engine](#communication-protocol-engine)
   - [Monitoring Engine](#monitoring-engine)
   - [Configuration Engine](#configuration-engine)
   - [Asyc Process Engine](#async-process-engine)
   - [Event Engine](#event-engine)
   - [Dependency Injection Engine](#dependency-injection-engine)
   - [Testing Engine](#testing-engine)
   - [Documentation Engine](#documentation-engine)
4. [Application Architecture](#application-architecture)
   - [Overview](#overview)
   - [Event-Driven Architecture](#event-driven-architecture)
   - [Dependency Injection and Inversion of Control](#dependency-injection-and-inversion-of-control)
   - ['Engine' Design Language](#engine-design-language)
5. [Future Plans](#future-plans)

<br>
<br>

# Getting Started

Getting started with Server++ is simple! We'll run through how to set up a basic API service, how to add new routes, and how to add some advanced features.

<br>
<br>

# About Server++

Server++ started as a passion project, which naturally grew into a much larger and more advanced (read: complicated) system and eventually the framework you see today.

Initially, this project was started with two purposes:

1. As a basis to advance my learning in low-level backend service design, architecture and related systems
2. As a project to display my knowledge, skills, and competency in backend server engineering

<br>
<br>

# Features

As described in the [Application Architecture](#application-architecture) section, Server++ employs an 'engine' design language. In the context of Server++, and 'engine' is defined as modular component or module that encapsulates a specific area of functionality or concern within Server++. This design language is used to help organise the different parts of the framework, and to help prevent unnecessary coupling of different areas of concern.

<br>

## Core Services Engine

The Core Services Engine provides the logic and functionality expected from a standard HTTP server, such as HTTP request parsing, processing, responding, and support for HTTPS.

### HTTP Request Parsing

### HTTP Request Processing

### HTTP Request Responding

### HTTPS Support

## Cryptography Engine

The Cryptography Engine provides key cryptography features like encryption, decryption, hashing, and generation of SSL certificates. The key design principle of the cryptography engine is that it is a transformational system: it receives an input, and returns an appropriate output. Whether this is encryption/decryption, hashing, obfuscation etc. the cryptography engine follows this transformation system structure to reduce complexity.

### Encryption/Decryption

### Hashing and Salting

### SSL Certificates

### Obfuscation

## Logging Engine

The Logging Engine provides simple application and processes logging functionality. This includes request/response logging, event logging, and error logging. It also provides analtyics services.

### Request/Response Loggin

### Event Logging

### Error Logging

### Analytics

## Caching Engine

The Caching Engine is responsible for creating, maintaining, monitoring, and invalidating the caching system in Server++.

### Cache Creation and Monitoring

### Cache Invalidation

## Load Balancing Engine

The Load Balancing Engine provides traffic management function for Server++.

### Load Balancing

### Multithreading and Additional Server++ Processes

An important part of load balancing is that there are other instances available to handle incoming traffic. Therefore, the Load Balancing Engine also handles the logic behind when to create or destroy a new instance of Server++, and ensuring these processes run in parallel to one-another. It's important to note that the specific functionality and logic behind enabling multithreading is handled by the [Async Process Engine](#async-process-engine), the Load Balancing Engine simply employs functionality from the Async Process Engine.

## Storage Engine

The Storage Engine allows Server++ to connect and interface with various data storage methods.

### Databases

### Other storage methods

## Proxy Engine

The Proxy Engine enables Server++ to act either as a forward or reverse proxy application.

### Forward Proxy

### Reverse Proxy

## Security Engine

The Security Engine is responsible for features related to keeping Server++ applications secure and safe, including rate limiting, autentication, and authorisation,

### Rate Limiting

### Authentication

### Authorisation

## Communication Protocol Engine

The Communication Protocol Engine handles logic and functionality behind the various communication protocols that Server++ supports, for example HTTP, HTTPS, SSH, SFTP, and more.

### HTTP and HTTPS

### SFTP

### SSH

### TCP/IP

### SMTP

## Monitoring Engine

The Monitoring Engine provides performance and usage tracking and statistics for Server++ processes.

### Performance Metrics

### Usage Metrics

### Health Checks

### Analytics

## Configuration Engine

The Configuration Engine manages configuration settings for Server++ and its features. It provides a centralised component for organising and managing any user-configurable settings.

## Async Process Engine

The Async Process Engine is responsible for managing the logic behind multithreading and creating/destroying other processes of Server++.

### Multithreading

### Creating/Destroying Application Processes

## Event Engine

The Event Engine implements the specifics of [Event-Driven Architecture](#event-driven-architecture) in Server++, such as event queuing and the publishing/subscribing process.

### Event Bus

### Event Queue

### Event Publishers

### Event Subscribers

### Event Handles

## Dependency Injection Engine

The Dependency Injection Engine implements the concept of [Inversion of Control](#dependency-injection-and-inversion-of-control) (IoC) in Server++.

### Dependency Injection (DI)

### DI Container

## Testing Engine

The Testing Engine provides automated testing functionality for many of the features in Server++.

## Documentation Engine

The Documentation Engine provides auto-documenation features, as well as an interface to provide extended documentation for application endpoints/paths.

<br>
<br>

# Application Architecture

Server++ is built on three high-level design choices/systems:

1. Event-Driven Architecture
2. Dependenct Injection
3. Engine Design Language

Each of these design choices/systems were chosen with the primary goal of reducing the complexity of Server++ during development, by ensuirng that decoupling during development is maintained and to reduce complex depdendencies between different areas of concerns. Given the already complex nature and many moving parts of this project, the last thing needed was further complexity.

## Event-Driven Architecture

Event-Driven Architecture (EDA) in it's most simpliest form is a software design system where decoupled parts of the same program run and communicate based on events. Events are triggered when some predefined action happens. Something that produces or triggers an event is a 'publisher', and something that reacts to that event happening is a 'subscriber'. In Server++, an example of an event is a HTTP response being sent back to a client. The [Core Services Engine](#core-services-engine) would be the publisher of the event in this context, and an example of a subscriber would be the [Logging Engine](#logging-engine) because it specifically responds to this event (logging the response sent back to the client).

The purpose of implementing EDA in Server++ is primarily to reduce any coupling between different areas of the framework, as mentioned above. Specifically though, EDA is used in Server++ to allow decoupled engines/services to operate independently of each other. In typical software applications, one object may itself call another object's functionality based on some condition. The issue with this though, is there is now a coupling between the two objects. Using EDA means that the logic for both objects is defined independently, and the functionality is instead triggered based on predefined events. This also allows us to better define when a particular feature or function should fire.

## Dependency Injection and Inversion of Control

Interconnected dependencies in programs is often a cause of headaches in complex projects. In this context, a dependency is something that a piece of software requires in order to run correctly. For Server++, this was a primary issue to be avoided given the size of the project.

To avoid this issue, Dependency Injection (DI) is utilised. Instead of the standard flow of control where objects define their own dependencies, DI allows us to instead inject the required dependencies into the given object. This further decouples sections of the program.

## Engine Design Language

You'll notice that each component of Server++ is called an 'Engine'. This design choice while mostly cosmetic, was chosen as a way of organising the separation of concerns. Think of it like a game engine, where components like the graphics engine, physics engine, audio engine etc. all come together to form the overall game engine. The same is true with Server++, each engine serves a specific purpose in a separated area of concern.

<br>
<br>

# Future Plans
